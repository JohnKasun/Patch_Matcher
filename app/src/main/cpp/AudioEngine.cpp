//
// Created by JohnK on 10/12/2021.
//

#include "AudioEngine.h"

AudioEngine::AudioEngine()
    : operator1(&sine, 1), operator2(&sine, 2), operator3(&sine, 3), operator4(&sine, 4), operator5(&sine, 5), operator6(&sine, 6),
    operator1_t(&sine, 1), operator2_t(&sine, 2), operator3_t(&sine, 3), operator4_t(&sine, 4), operator5_t(&sine, 5),operator6_t(&sine, 6)
{
    loadWavetables();
    initializeAudio();
    initializeTargetOperators();
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
            ->setPerformanceMode(oboe::PerformanceMode::LowLatency)
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
    return static_cast<int32_t>(mStream->requestPause());
}

oboe::DataCallbackResult AudioEngine::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) {
    float *floatData = (float *) audioData;
    for (int frame = 0; frame < numFrames; frame++)
    {
        float fSampleValue{kAmplitude};
        if (shouldPlayUser)
            fSampleValue *= outputTerminal.getNextSample();
        else
            fSampleValue *= outputTerminal_t.getNextSample();
        for (int channel = 0; channel < kChannelCount; channel++)
            floatData[frame * kChannelCount + channel] = fSampleValue;
    }
    return oboe::DataCallbackResult::Continue;
}

void AudioEngine::changeWavetable(int iOperatorId, Wavetable::Wavetable_t eWaveType)
{
    Operator* pOperator = operatorInterface[iOperatorId];
    switch(eWaveType)
    {
        case Wavetable::kSine:
            pOperator->setWavetable(&sine);
            break;
        case Wavetable::kSquare:
            pOperator->setWavetable(&square);
            break;
        case Wavetable::kTriangle:
            pOperator->setWavetable(&triangle);
            break;
        case Wavetable::kSaw:
            pOperator->setWavetable(&sawtooth);
            break;
        default:
            pOperator->setWavetable(&custom);
    }
}

void AudioEngine::loadWavetables()
{
    sine.generate();
    square.generate();
    triangle.generate();
    sawtooth.generate();
    custom.setPatch([](float theta) { return (float)(sin(theta) + 0.5 * sin(2.0*theta) * 0.25 * sin(3.0 * theta));});
    custom.generate();
}

void AudioEngine::initializeTargetOperators()
{
    targetGenerator.setMaxFrequency(5000);
    targetGenerator.setMaxGain(Operator::getMaxGain());
    targetGenerator.generateParameters();

    for (int i = 1; i <= targetGenerator.getConnectionSetup().iNumActiveOperators; i++)
    {
        Parameters operatorParameters = targetGenerator.getOperatorParameters(i);
        setTargetParameters(operatorInterface_t[i-1],&operatorParameters);
    }

}

void AudioEngine::setTargetParameters(Operator* operatorToSet, const Parameters* opParameters) {
    operatorToSet->setFrequency(opParameters->fFreq);
    operatorToSet->setGain(opParameters->fGain);
    operatorToSet->setFeedbackGain(opParameters->fFeedback);
    if (!opParameters->operatorIds.empty())
    {
        for (int operatorId : opParameters->operatorIds)
        {
            operatorId -= 1;
            if (operatorId == -1)
                operatorToSet->connectTo(&outputTerminal_t);
            else
                operatorToSet->connectTo(operatorInterface_t[operatorId]);
        }
    }
}

void AudioEngine::regenerateTarget()
{
    outputTerminal_t.reset();
    for (Operator* op : operatorInterface_t)
        op->reset();
    initializeTargetOperators();
}

std::string AudioEngine::getTargetValues() {
    std::stringstream iss;
    for (int i = 1; i <= targetGenerator.getConnectionSetup().iNumActiveOperators; i++)
    {
        iss << "Operator " << i << "-";
        Parameters opParameters = targetGenerator.getOperatorParameters(i);
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
    for (Operator* op : operatorInterface)
        op->resetPhase();
}

void AudioEngine::setUserParameters(Operator *operatorToSet, const Parameters *parameters) {
    operatorToSet->setFrequency(parameters->fFreq);
    operatorToSet->setGain(parameters->fGain);
    operatorToSet->setFeedbackGain(parameters->fFeedback);
    if (!parameters->operatorIds.empty())
    {
        for (int operatorId : parameters->operatorIds)
        {
            operatorId -= 1;
            if (operatorId == -1)
                operatorToSet->connectTo(&outputTerminal);
            else
                operatorToSet->connectTo(operatorInterface[operatorId]);
        }
    }
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


