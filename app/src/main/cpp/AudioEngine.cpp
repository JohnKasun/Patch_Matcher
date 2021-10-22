//
// Created by JohnK on 10/12/2021.
//

#include "AudioEngine.h"

AudioEngine::AudioEngine() : osc(sine), osc2(custom)
{
    loadWavetables();
}

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
    osc.setFrequency(440.0f, builder.getSampleRate());
    osc2.setFrequency(554.38, builder.getSampleRate());
    mStream->requestFlush();
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
        float sampleValue = kAmplitude * (osc.getNextSample() + osc2.getNextSample());
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
