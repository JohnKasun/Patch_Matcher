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
    static float constexpr kPI = M_PI;
    static float constexpr kTwoPi = kPI * 2.0;
    const Wavetable* wavetable;
    int tableSize;
    float accumulatedPhase;
    float phaseDelta;
    float frequency;
    float gain;
    float currentSample;
public:
    WavetableOscillator(const Wavetable* wavetableToUse);
    virtual ~WavetableOscillator();

    void setFrequency(float freq, float sampleRate);
    float getFrequency() const;
    void setWavetable(const Wavetable* newWavetable);
    void setGain(float newGain);
    virtual inline float getNextSample() noexcept = 0;
    float getCurrentSample() const { return currentSample; };
};


#endif //PATCH_MATCHER_WAVETABLEOSCILLATOR_H
