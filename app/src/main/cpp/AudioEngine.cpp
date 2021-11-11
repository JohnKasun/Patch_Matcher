//
// Created by JohnK on 10/12/2021.
//

#include "AudioEngine.h"

AudioEngine::AudioEngine() : operatorA(&sine), operatorB(&sine), operatorC(&sine), operatorD(&sine)
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
    return (int32_t) mStream->requestStart();
}

void AudioEngine::stopAudio()
{
    // Stop, close and delete in case not already closed.
    std::lock_guard<std::mutex> lock(mLock);
    if (mStream) {
        mStream->stop();
        mStream->close();
        mStream.reset();
    }
}

int32_t AudioEngine::pauseAudio()
{
    oboe::StreamState inputState = oboe::StreamState::Pausing;
    oboe::StreamState nextState = oboe::StreamState::Uninitialized;
    int64_t timeoutNanos = 100 * oboe::kNanosPerMillisecond;
    mStream->requestPause();
    return (int32_t) mStream->waitForStateChange(inputState, &nextState, timeoutNanos);
}

oboe::DataCallbackResult AudioEngine::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames)
{
    float *floatData = (float *) audioData;
    for (int i = 0; i < numFrames; ++i) {
        float sampleValue = operatorA.getNextSample();
        for (int j = 0; j < kChannelCount; j++) {
            floatData[i * kChannelCount + j] = sampleValue;
        }
    }
    return oboe::DataCallbackResult::Continue;
}

void AudioEngine::loadWavetables()
{
    sine.generate();
    square.generate();
    custom.setPatch([](double theta) {
        return (sinf(theta) + 0.5 * sinf(2.0*theta) * 0.25 * sinf(3.0 * theta));
    });
    custom.generate();
}

void AudioEngine::changeWavetable()
{
    static int type {0};
    switch (++type % 3){
        case 0: operatorA.setWavetable(&sine);  break;
        case 1: operatorA.setWavetable(&square);  break;
        default: operatorA.setWavetable(&custom);
    }
}

void AudioEngine::initializeOperators()
{
    operatorA.setFrequency(210.0f, kSampleRate);
    operatorA.setGain(0.5f);
    operatorB.setFrequency(35.0f, kSampleRate);
    operatorB.setGain(10.0f);
    operatorC.setFrequency(280, kSampleRate);
    operatorC.setGain(0.5);
    operatorD.setFrequency(0.1, kSampleRate);
    operatorD.setGain(20.0);

    operatorB.connectTo(&operatorA);
    operatorB.connectTo(&operatorC);
    operatorC.connectTo(&operatorA);
}
