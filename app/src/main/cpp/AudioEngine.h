//
// Created by JohnK on 10/12/2021.
//

#ifndef PATCH_MATCHER_AUDIOENGINE_H
#define PATCH_MATCHER_AUDIOENGINE_H
#include <oboe/Oboe.h>
#include <string>

#include "Operator.h"
#include "TargetGenerator.h"
#include "LevelGenerator.h"

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

    // Target Operators Interface
    OutputTerminal outputTerminal_t;
    Operator operatorInterface_t[maxOperators] {
            Operator(&sine, 1),
            Operator(&sine, 2),
            Operator(&sine, 3),
            Operator(&sine, 4),
            Operator(&sine, 5),
            Operator(&sine, 6)
    };

    TargetGenerator targetGenerator;
    LevelGenerator levelGenerator;
    Parameters parameterInterface_t[maxOperators] {
            Parameters(),
            Parameters(),
            Parameters(),
            Parameters(),
            Parameters(),
            Parameters()
    };

    // Startup Functions
    void initializeTargetOperators();
    void setOperatorParameters(Operator (&allOperators)[maxOperators], Parameters (&allParameters)[maxOperators], OutputTerminal* outputTerminal);

    const char* wavetableToString(const Wavetable::Wavetable_t eWaveType) const;
    Wavetable& getWavetableReference(const Wavetable::Wavetable_t eWaveType);

    bool m_bIsProcessing = false;

public:
    AudioEngine();
    virtual ~AudioEngine();

    int32_t initializeAudio();
    int32_t startAudio();
    void stopAudio();
    int32_t pauseAudio();
    oboe::DataCallbackResult onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) override;

    void changeWavetable(int iOperatorId, Wavetable::Wavetable_t eWaveType);
    double getSampleRate() { return kSampleRate; };
    void setOutputType(bool shouldPlayUser) { this->shouldPlayUser = shouldPlayUser; };
    bool isRunning() const { return m_isRunning; };
    void regenerateTarget();
    std::string getTargetValues();
    void initializeUserPatch();
    float evaluatePatch();
    void reset();

    void setLevelPatch(int level);
    void setTutorialPatch();

    OutputTerminal outputTerminal;
    Operator operatorInterface[maxOperators] {
            Operator(&sine, 1),
            Operator(&sine, 2),
            Operator(&sine, 3),
            Operator(&sine, 4),
            Operator(&sine, 5),
            Operator(&sine, 6)
    };

    Parameters parameterInterface[maxOperators] {
            Parameters(),
            Parameters(),
            Parameters(),
            Parameters(),
            Parameters(),
            Parameters()
    };


};


#endif //PATCH_MATCHER_AUDIOENGINE_H
