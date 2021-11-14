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
    static double constexpr kPI = M_PI;
    static double constexpr kTwoPi = kPI * 2.0;
    const Wavetable* wavetable;
    int tableSize;
    double accumulatedPhase = 0.0;
    double phaseDelta;
    double frequency = 0.0;
    double gain = 0.0;
    double currentSample = 0.0;
public:
    WavetableOscillator(const Wavetable* wavetableToUse);
    virtual ~WavetableOscillator();

    void setFrequency(double freq, double sampleRate);
    double getFrequency() const;
    void setWavetable(const Wavetable* newWavetable);
    void setGain(double newGain);
    virtual inline double getNextSample() noexcept = 0;
    double getCurrentSample() const { return currentSample; };
};


#endif //PATCH_MATCHER_WAVETABLEOSCILLATOR_H
