//
// Created by JohnK on 10/12/2021.
//

#ifndef PATCH_MATCHER_WAVETABLEOSCILLATOR_H
#define PATCH_MATCHER_WAVETABLEOSCILLATOR_H
#include "Wavetable.h"


class WavetableOscillator
{
private:
    const Wavetable &wavetable;
    const unsigned tableSize;
    float currentIndex = 0.0f;
    float tableDelta = 0.0f;
public:
    WavetableOscillator(const Wavetable &wavetableToUse);
    ~WavetableOscillator();

    void setFrequency(float frequency, float sampleRate);
    inline float getNextSample() noexcept
    {
        auto index0 = (unsigned) currentIndex;
        auto index1 = (index0 == (tableSize-1) ? (unsigned) 0 : index0 + 1);

        auto frac = currentIndex - (float)index0;

        float value0 = wavetable[index0];
        float value1 = wavetable[index1];

        float currentSample = value0 + frac * (value1 - value0);

        if ((currentIndex += tableDelta) > (float)tableSize)
            currentIndex -= (float)tableSize;

        return currentSample;
    }

};


#endif //PATCH_MATCHER_WAVETABLEOSCILLATOR_H
