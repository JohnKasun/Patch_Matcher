//
// Created by JohnK on 10/12/2021.
//

#include "AudioEngine.h"

AudioEngine::AudioEngine()
{
    initializeAudio();
}

AudioEngine::~AudioEngine()
{
    stopAudio();
}

int32_t AudioEngine::initializeAudio()
{
    std::lock_guard<std::mutex> lock(mLock);
    oboe::AudioStreamBuilder builder;
    // The builder set methods can be chained for convenience.
    oboe::Result result = builder.setSharingMode(oboe::SharingMode::Exclusive)
            ->setPerformanceMode(oboe::PerformanceMode::PowerSaving)
            ->setChannelCount(kChannelCount)
            ->setSampleRate(kSampleRate)
            ->setSampleRateConversionQuality(oboe::SampleRateConversionQuality::Medium)
            ->setFormat(oboe::AudioFormat::Float)
            ->setDataCallback(this)
            ->openStream(mStream);
    WavetableOscillator::setSampleRate(kSampleRate);
    return (int32_t) result;
}

int32_t AudioEngine::startAudio()
{
    // Typically, start the stream after querying some stream information, as well as some input from the user
    m_isRunning = true;
    return (int32_t) mStream->requestStart();
}

void AudioEngine::stopAudio()
{
    // Stop, close and delete in case not already closed.
    m_isRunning = false;
    std::lock_guard<std::mutex> lock(mLock);
    if (mStream) {
        mStream->stop();
        mStream->close();
        mStream.reset();
    }
}

int32_t AudioEngine::pauseAudio()
{
    m_isRunning = false;
    oboe::Result result = mStream->requestPause();
    return static_cast<int32_t>(result);
}

oboe::DataCallbackResult AudioEngine::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) {
    float *floatData = (float *) audioData;
    if (shouldPlayUser) {
        for (int i = 0; i < numFrames; ++i) {
            float sampleValue = (float) outputTerminal.getNextSample();
            for (int j = 0; j < kChannelCount; j++) {
                floatData[i * kChannelCount + j] = sampleValue / kChannelCount;
            }
        }
    } else {
        for (int i = 0; i < numFrames; ++i) {
            float sampleValue = (float) outputTerminal_t.getNextSample();
            for (int j = 0; j < kChannelCount; j++) {
                floatData[i * kChannelCount + j] = sampleValue / kChannelCount;
            }
        }
    }
    return oboe::DataCallbackResult::Continue;
}

void AudioEngine::setOperatorParameters(Operator (&allOperators)[maxOperators], Parameters (&allParameters)[maxOperators], OutputTerminal *outputTerminal)
{
    for (int i = 0; i < maxOperators; i++)
    {
        Operator& operatorToSet = allOperators[i];
        Parameters& parameters = allParameters[i];

        operatorToSet.setFrequency(parameters.fFreq);
        operatorToSet.setGain(parameters.fGain);
        operatorToSet.setFeedbackGain(parameters.fFeedback);
        operatorToSet.setWavetable(&getWavetableReference(parameters.eWaveType));
        if (!parameters.operatorIds.empty())
        {
            for (int operatorId : parameters.operatorIds)
            {
                operatorId -= 1;
                if (operatorId == -1)
                    operatorToSet.connectTo(outputTerminal);
                else
                    operatorToSet.connectTo(&allOperators[operatorId]);
            }
        }

    }

}

void AudioEngine::changeWavetable(int iOperatorId, Wavetable::Wavetable_t eWaveType)
{
    Operator& pOperator = operatorInterface[iOperatorId];
    switch(eWaveType)
    {
        case Wavetable::kSine:
            pOperator.setWavetable(&sine);
            break;
        case Wavetable::kSquare:
            pOperator.setWavetable(&square);
            break;
        case Wavetable::kTriangle:
            pOperator.setWavetable(&triangle);
            break;
        case Wavetable::kSaw:
            pOperator.setWavetable(&sawtooth);
            break;
        default:
            pOperator.setWavetable(&custom);
    }
}

void AudioEngine::initializeTargetOperators()
{
    targetGenerator.setMaxFrequency(5000);
    targetGenerator.setMaxGain(Operator::getMaxGain());
    targetGenerator.generateParameters();
    for (int i = 0; i < maxOperators; i++)
    {
        parameterInterface_t[i] = targetGenerator.getOperatorParameters(i+1);
    }
    setOperatorParameters(operatorInterface_t, parameterInterface_t, &outputTerminal_t);

}

void AudioEngine::regenerateTarget()
{
    outputTerminal_t.reset();
    for (Operator& op : operatorInterface_t)
    {
        op.reset();
        op.setWavetable(&sine);
    }
    for (Parameters& param : parameterInterface_t)
    {
        param.reset();
    }

    initializeTargetOperators();
}

std::string AudioEngine::getTargetValues() {
    std::stringstream iss;
    for (int i = 1; i <= 6; i++)
    {
        iss << "Operator " << i << "-";
        Parameters opParameters = parameterInterface_t[i-1];
        iss << "\n\t " << opParameters.fFreq << "Hz "
                        << opParameters.fGain << " "
                        << opParameters.fFeedback * 100 << "% "
                        << wavetableToString(opParameters.eWaveType);
        iss << "\n\tConnected to: ";
        for (const auto& opId : opParameters.operatorIds)
            iss << opId << " ";
        iss << "\n";
    }
    return iss.str();
}

void AudioEngine::initializeUserPatch() {
    for (Operator& op : operatorInterface)
        op.resetPhase();
}

const char* AudioEngine::wavetableToString(const Wavetable::Wavetable_t eWaveType) const {
    switch (eWaveType)
    {
        case Wavetable::kSine:
            return "Sine";
        case Wavetable::kSquare:
            return "Square";
        case Wavetable::kTriangle:
            return "Triangle";
        case Wavetable::kSaw:
            return "Sawtooth";
        default:
            return "Custom";
    }
}

Wavetable& AudioEngine::getWavetableReference(const Wavetable::Wavetable_t eWaveType) {
    switch (eWaveType)
    {
        case Wavetable::kSine:
            return sine;
        case Wavetable::kSquare:
            return square;
        case Wavetable::kTriangle:
            return triangle;
        case Wavetable::kSaw:
            return sawtooth;
        default:
            return custom;
    }
}

void AudioEngine::reset()
{
    outputTerminal.reset();
    for (Operator& op : operatorInterface)
    {
        op.reset();
        op.setWavetable(&sine);
    }
    outputTerminal_t.reset();
    for (Operator& op : operatorInterface_t)
    {
        op.reset();
        op.setWavetable(&sine);
    }
    for (Parameters& params : parameterInterface)
        params.reset();
    for (Parameters& params : parameterInterface_t)
        params.reset();
}

float AudioEngine::evaluatePatch()
{
    while (m_bIsProcessing);

    OutputTerminal outputTerminalUser;
    Operator operatorInterfaceUser[maxOperators] {
            Operator(&sine, 1),
            Operator(&sine, 2),
            Operator(&sine, 3),
            Operator(&sine, 4),
            Operator(&sine, 5),
            Operator(&sine, 6)
    };

    OutputTerminal outputTerminalTarget;
    Operator operatorInterfaceTarget[maxOperators] {
            Operator(&sine, 1),
            Operator(&sine, 2),
            Operator(&sine, 3),
            Operator(&sine, 4),
            Operator(&sine, 5),
            Operator(&sine, 6)
    };

    setOperatorParameters(operatorInterfaceUser, parameterInterface, &outputTerminalUser);
    setOperatorParameters(operatorInterfaceTarget, parameterInterface_t, &outputTerminalTarget);

    float fLowestFreq = std::min(outputTerminalUser.getLowestFrequency(), outputTerminalTarget.getLowestFrequency());
    if (fLowestFreq == 0)
        return 0;

    float fSmallestPeriod = 1.0f / fLowestFreq;
    int numSamples = static_cast<int>(fSmallestPeriod * kSampleRate);
    std::vector<float> userSamples;
    std::vector<float> targetSamples;

    // Generate samples and place into buffer for processing
    for (int sample = 0; sample < numSamples; sample++)
    {
        userSamples.push_back(outputTerminalUser.getNextSample());
        targetSamples.push_back(outputTerminalTarget.getNextSample());
    }

    // Find max value for each buffer
    float userMax = userSamples[0];
    float targetMax = targetSamples[0];
    for (int sample = 0; sample < numSamples; sample++)
    {
        if (userSamples[sample] > userMax)
            userMax = userSamples[sample];

        if (targetSamples[sample] > targetMax)
            targetMax = targetSamples[sample];
    }
    if (userMax == 0)
        return 0;

    // Normalize each buffer
    for (int sample = 0; sample < numSamples; sample++)
    {
        userSamples[sample] /= userMax;
        targetSamples[sample] /= targetMax;
    }

    // Calculate mean diff
    float diffSum = 0;
    for (int sample = 0; sample < numSamples; sample++)
    {
        diffSum += abs(userSamples[sample] - targetSamples[sample]);
    }
    float diffMean = diffSum / numSamples;

    // Scores the patch
    const float iLowerBound = 1E-2;
    const float iUpperBound = 1.0;
    float fScore = 0;
    if (diffMean <= iLowerBound)
        fScore = 100.0f;
    else if (diffMean >= iUpperBound)
        fScore = 0.0f;
    else
    {
        fScore = (diffMean - iUpperBound) / (iLowerBound - iUpperBound) * 100.0f;
    }
    return fScore;


}

void AudioEngine::setLevelPatch(int level)
{
    LevelParameters levelParameters = levelGenerator.getLevelParameters(level);
    parameterInterface_t[0] = levelParameters.Operator1;
    parameterInterface_t[1] = levelParameters.Operator2;
    parameterInterface_t[2] = levelParameters.Operator3;
    parameterInterface_t[3] = levelParameters.Operator4;
    parameterInterface_t[4] = levelParameters.Operator5;
    parameterInterface_t[5] = levelParameters.Operator6;
    setOperatorParameters(operatorInterface_t, parameterInterface_t, &outputTerminal_t);
}

void AudioEngine::setTutorialPatch()
{
    LevelParameters levelParameters = levelGenerator.getTutorialParameters();
    parameterInterface_t[0] = levelParameters.Operator1;
    parameterInterface_t[1] = levelParameters.Operator2;
    parameterInterface_t[2] = levelParameters.Operator3;
    parameterInterface_t[3] = levelParameters.Operator4;
    parameterInterface_t[4] = levelParameters.Operator5;
    parameterInterface_t[5] = levelParameters.Operator6;
    setOperatorParameters(operatorInterface_t, parameterInterface_t, &outputTerminal_t);
}


