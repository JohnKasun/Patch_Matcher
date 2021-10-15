//
// Created by JohnK on 10/12/2021.
//

#include "AudioEngine.h"

AudioEngine::AudioEngine(){}

int32_t AudioEngine::startAudio()
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
    if (result != oboe::Result::OK) return (int32_t) result;

    // Typically, start the stream after querying some stream information, as well as some input from the user
    result = mStream->requestStart();
    return (int32_t) result;
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

oboe::DataCallbackResult AudioEngine::onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames)
{
    float *floatData = (float *) audioData;
    for (int i = 0; i < numFrames; ++i) {
        float sampleValue = kAmplitude * sinf(mPhase);
        for (int j = 0; j < kChannelCount; j++) {
            floatData[i * kChannelCount + j] = sampleValue;
        }
        mPhase += mPhaseIncrement;
        if (mPhase >= kTwoPi) mPhase -= kTwoPi;
    }
    return oboe::DataCallbackResult::Continue;
}

void AudioEngine::loadWavetables()
{
    Wavetable sineWavetable([](double currentAngle){ return sinf(currentAngle);});

    wavetables["Sine"] = &sineWavetable;
}
