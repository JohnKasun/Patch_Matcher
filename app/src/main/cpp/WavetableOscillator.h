//
// Created by JohnK on 10/12/2021.
//

#ifndef PATCH_MATCHER_WAVETABLEOSCILLATOR_H
#define PATCH_MATCHER_WAVETABLEOSCILLATOR_H
#include "Wavetable.h"
#include <fstream>


class WavetableOscillator
{
protected:
    const Wavetable* wavetable;
    int tableSize;
    float currentIndex = 0.0f;
    float tableDelta = 0.0f;
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
    inline float getCurrentSample() const noexcept { return currentSample; };
    virtual inline void generateNextSample() noexcept = 0;
};


#endif //PATCH_MATCHER_WAVETABLEOSCILLATOR_H
