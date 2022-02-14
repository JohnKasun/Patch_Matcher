//
// Created by JohnK on 10/12/2021.
//

#include "AudioEngine.h"

AudioEngine::AudioEngine()
    : operator1(&sine), operator2(&sine), operator3(&sine), operator4(&sine), operator5(&sine), operator6(&sine),
    operator1_t(&sine), operator2_t(&sine), operator3_t(&sine), operator4_t(&sine), operator5_t(&sine),operator6_t(&sine)
{
    loadWavetables();
    initializeAudio();
    initializeOperators();
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
    if (shouldPlayUser) {
        for (int i = 0; i < numFrames; ++i) {
            float sampleValue = (float) outputTerminal.getNextSample();
            for (int j = 0; j < kChannelCount; j++) {
                floatData[i * kChannelCount + j] = sampleValue;
            }
        }
    } else {
        for (int i = 0; i < numFrames; ++i) {
            float sampleValue = (float) outputTerminal_t.getNextSample();
            for (int j = 0; j < kChannelCount; j++) {
                floatData[i * kChannelCount + j] = sampleValue;
            }
        }
    }
    return oboe::DataCallbackResult::Continue;
}

void AudioEngine::changeWavetable(int iOperatorId, int iWavetableType)
{
    Operator* pOperator = operatorInterface[iOperatorId];
    switch(iWavetableType)
    {
        case 0:
            pOperator->setWavetable(&sine);
            break;
        case 1:
            pOperator->setWavetable(&square);
            break;
        case 2:
            pOperator->setWavetable(&triangle);
            break;
        case 3:
            pOperator->setWavetable(&sawtooth);
            break;
        case 4:
            pOperator->setWavetable(&custom);
    }
}

void AudioEngine::loadWavetables()
{
    sine.generate();
    square.generate();
    triangle.generate();
    sawtooth.generate();
    custom.setPatch([](float theta) {
        return (float)(sin(theta) + 0.5 * sin(2.0*theta) * 0.25 * sin(3.0 * theta));
    });
    custom.generate();
}

void AudioEngine::initializeOperators()
{
    float fMaxGain = Operator::getMaxGain();
    operator1_t.setFrequency(440.0f);
    operator1_t.setGain(fMaxGain);
    operator1_t.connectTo(&outputTerminal_t);

    operator2_t.setFrequency(0.0f);
    operator2_t.setGain(0.0f);
    operator2_t.connectTo(&outputTerminal_t);
}
