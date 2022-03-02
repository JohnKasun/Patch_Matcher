//
// Created by JohnK on 10/12/2021.
//

#ifndef PATCH_MATCHER_AUDIOENGINE_H
#define PATCH_MATCHER_AUDIOENGINE_H
#include <oboe/Oboe.h>
#include <string>

#include "Operator.h"
#include "TargetGenerator.h"

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
    TriangleWavetable triangle;
    SawtoothWavetable sawtooth;
    CustomWavetable custom;

    // Operators
    Operator operator1;
    Operator operator2;
    Operator operator3;
    Operator operator4;
    Operator operator5;
    Operator operator6;
    Parameters m_param1;
    Parameters m_param2;
    Parameters m_param3;
    Parameters m_param4;
    Parameters m_param5;
    Parameters m_param6;



    // Target Operators
    Operator operator1_t;
    Operator operator2_t;
    Operator operator3_t;
    Operator operator4_t;
    Operator operator5_t;
    Operator operator6_t;
    OutputTerminal outputTerminal_t;
    TargetGenerator targetGenerator;

    // Target Operators Interface
    Operator* operatorInterface_t[maxOperators] {
            &operator1_t,
            &operator2_t,
            &operator3_t,
            &operator4_t,
            &operator5_t,
            &operator6_t,
    };

    // Startup Functions
    void loadWavetables();
    void initializeOperators();
    void setTargetParameters(Operator* operatorToSet, const Parameters* parameters);
    void setUserParameters(Operator* operatorToSet, const Parameters* parameters);

public:
    AudioEngine();
    virtual ~AudioEngine();

    int32_t initializeAudio();
    int32_t startAudio();
    void stopAudio();
    int32_t pauseAudio();
    oboe::DataCallbackResult onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) override;

    void reinitializeUserPatch();
    void changeWavetable(int iOperatorId, int iWavetableType);
    double getSampleRate() { return kSampleRate; };
    void setOutputType(bool shouldPlayUser) { this->shouldPlayUser = shouldPlayUser; };
    bool isRunning() const { return m_isRunning; };
    void regenerateTarget();
    std::string getTargetValues();


    OutputTerminal outputTerminal;
    Operator* operatorInterface[maxOperators] {
        &operator1,
        &operator2,
        &operator3,
        &operator4,
        &operator5,
        &operator6,
        };

    Parameters* parameterInterface[maxOperators] {
        &m_param1,
        &m_param2,
        &m_param3,
        &m_param4,
        &m_param5,
        &m_param6
    };


};


#endif //PATCH_MATCHER_AUDIOENGINE_H
