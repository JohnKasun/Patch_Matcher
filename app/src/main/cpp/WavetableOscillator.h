//
// Created by JohnK on 10/12/2021.
//

#ifndef PATCH_MATCHER_WAVETABLEOSCILLATOR_H
#define PATCH_MATCHER_WAVETABLEOSCILLATOR_H
#include "Wavetable.h"
#include <fstream>


class WavetableOscillator
{
private:
    const Wavetable* wavetable;
    int tableSize;
    float currentIndex = 0.0f;
    float tableDelta = 0.0f;
    float frequency = 0.0f;
public:
    WavetableOscillator(const Wavetable* wavetableToUse);
    ~WavetableOscillator();

    void setFrequency(float freq, float sampleRate);
    float getTableDelta() const;
    float getFrequency() const;
    void setWavetable(const Wavetable* newWavetable);
    inline float getNextSample() noexcept
    {
        int indexBelow = (int) currentIndex;
        int indexAbove = indexBelow + 1;
        if (indexAbove >= tableSize)
            indexAbove = 0;

        float fracAbove = currentIndex - indexBelow;
        float fracBelow = 1.0 - fracAbove;

        float currentSample = (fracBelow * wavetable->at(indexBelow)) + (fracAbove * wavetable->at(indexAbove));

        currentIndex += tableDelta;
        while(currentIndex >= (float)tableSize)
            currentIndex -= tableSize;

        return currentSample;
    }

};


#endif //PATCH_MATCHER_WAVETABLEOSCILLATOR_H
