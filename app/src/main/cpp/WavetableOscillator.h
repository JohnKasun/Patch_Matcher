//
// Created by JohnK on 10/12/2021.
//

#ifndef PATCH_MATCHER_WAVETABLEOSCILLATOR_H
#define PATCH_MATCHER_WAVETABLEOSCILLATOR_H
#include "Wavetable.h"
#include <cmath>
#include <fstream>


class WavetableOscillator
{
protected:
    static float constexpr s_fMaxGain = 100.0f;
    static float constexpr s_fMaxGainScaling = 1.0f / s_fMaxGain;
    static float constexpr kPI = M_PI;
    static float constexpr kTwoPi = kPI * 2.0;
    static float s_fSampleRate;
    static float s_FREQ_TO_PHASEDELTA;
    static float s_PHASEDELTA_TO_FREQ;


    const Wavetable* m_pWavetable;

    int m_iTableSize;
    float m_fAccumulatedPhase;
    float m_fPhaseDelta;
    float m_fGain;
    float m_fCurrentSample;

public:
    WavetableOscillator(const Wavetable* wavetableToUse);
    virtual ~WavetableOscillator();

    void setFrequency(float freq);
    float getFrequency() const;
    void setWavetable(const Wavetable* newWavetable);
    void setGain(float newGain);
    float getGain() const;
    float getCurrentSample() const { return m_fCurrentSample; };

    virtual inline float getNextSample() noexcept = 0;
    static void setSampleRate(float fSampleRate);
};


#endif //PATCH_MATCHER_WAVETABLEOSCILLATOR_H
