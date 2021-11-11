//
// Created by JohnK on 10/12/2021.
//

#ifndef PATCH_MATCHER_AUDIOENGINE_H
#define PATCH_MATCHER_AUDIOENGINE_H
#include <oboe/Oboe.h>
#include <unordered_map>
#include <string>

#include "Wavetable.h"
#include "SineWavetable.h"
#include "SquareWavetable.h"
#include "CustomWavetable.h"
#include "WavetableOscillator.h"
#include "Operator.h"

class AudioEngine : public oboe::AudioStreamCallback{
public:
    AudioEngine();
    virtual ~AudioEngine();

    int32_t initializeAudio();
    int32_t startAudio();
    void stopAudio();
    int32_t pauseAudio();
    oboe::DataCallbackResult onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) override;

    void changeWavetable();

private:
    std::mutex         mLock;
    std::shared_ptr<oboe::AudioStream> mStream;

    // Stream params
    static int constexpr kChannelCount = 2;
    static int constexpr kSampleRate = 48000;
    // Wave params, these could be instance variables in order to modify at runtime
    static float constexpr kAmplitude = 0.5f;

    // Wavetables
    SineWavetable sine;
    SquareWavetable square;
    CustomWavetable custom;

    // Operators
    Operator operatorA;
    Operator operatorB;
    Operator operatorC;
    Operator operatorD;

    // Load Wavetables on startup
    void loadWavetables();

    void initializeOperators();
};


#endif //PATCH_MATCHER_AUDIOENGINE_H
