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
    oboe::StreamState inputState = oboe::StreamState::Pausing;
    oboe::StreamState nextState = oboe::StreamState::Uninitialized;
    int64_t timeoutNanos = 100 * oboe::kNanosPerMillisecond;
    mStream->requestPause();
    return (int32_t) mStream->waitForStateChange(inputState, &nextState, timeoutNanos);
}

oboe::DataCallbackResult AudioEngine::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) {
    float *floatData = (float *) audioData;
    if (shouldPlayUser) {
        for (int i = 0; i < numFrames; ++i) {
            float sampleValue = (float) outputTerminal.getNextSample();
            for (const auto cOperator : operatorInterface)
                cOperator->resetGeneration();
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

void AudioEngine::loadWavetables()
{
    sine.generate();
    square.generate();
    custom.setPatch([](double theta) {
        return (sin(theta) + 0.5 * sin(2.0*theta) * 0.25 * sin(3.0 * theta));
    });
    custom.generate();
}

void AudioEngine::changeWavetable()
{
    static int type {0};
    switch (++type % 3){
        case 0: operator1.setWavetable(&sine);  break;
        case 1: operator1.setWavetable(&square);  break;
        default: operator1.setWavetable(&custom);
    }
}

void AudioEngine::initializeOperators()
{
    operator1_t.setFrequency(440.0, kSampleRate);
    operator1_t.setGain(0.5f);
    operator1_t.connectTo(&outputTerminal_t);
}
