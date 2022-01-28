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
private:

    std::mutex         mLock;
    std::shared_ptr<oboe::AudioStream> mStream;

    static int constexpr kChannelCount = 2;
    static int constexpr kSampleRate = 48000;
    static float constexpr kAmplitude = 0.5f;
    static int constexpr maxOperators = 6;
    bool shouldPlayUser = true;
    bool m_isRunning = false;

    // Wavetables
    SineWavetable sine;
    SquareWavetable square;
    CustomWavetable custom;

    // Operators
    Operator operator1;
    Operator operator2;
    Operator operator3;
    Operator operator4;
    Operator operator5;
    Operator operator6;

    // Target Operators
    Operator operator1_t;
    Operator operator2_t;
    Operator operator3_t;
    Operator operator4_t;
    Operator operator5_t;
    Operator operator6_t;
    OutputTerminal outputTerminal_t;

    // Startup Functions
    void loadWavetables();
    void initializeOperators();

public:
    AudioEngine();
    virtual ~AudioEngine();

    int32_t initializeAudio();
    int32_t startAudio();
    void stopAudio();
    int32_t pauseAudio();
    oboe::DataCallbackResult onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) override;

    void changeWavetable();
    double getSampleRate() { return kSampleRate; };
    void enableFeedback() { operator1.connectTo(&operator1);};
    void setOutputType(bool shouldPlayUser) { this->shouldPlayUser = shouldPlayUser; };
    bool isRunning() const { return m_isRunning; };
    void reset();

    OutputTerminal outputTerminal;
    Operator* operatorInterface[maxOperators] {
        &operator1,
        &operator2,
        &operator3,
        &operator4,
        &operator5,
        &operator6,
        };

};


#endif //PATCH_MATCHER_AUDIOENGINE_H
