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
    static float constexpr kTwoPi = kPI * 2;
    const Wavetable* wavetable;
    int tableSize;
    //float currentIndex = 0.0f;
    float accumulatedPhase = 0.0f;
    //float tableDelta = 0.0f;
    float phaseDelta;
    float frequency = 0.0f;
    float gain = 0.0f;
    float currentSample = 0.0f;
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
