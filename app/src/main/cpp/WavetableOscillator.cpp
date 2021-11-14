//
// Created by JohnK on 10/12/2021.
//

#include "WavetableOscillator.h"
WavetableOscillator::WavetableOscillator(const Wavetable* wavetableToUse) : wavetable{wavetableToUse}, tableSize{wavetableToUse->get_size()}
{
}

WavetableOscillator::~WavetableOscillator()
{
}

void WavetableOscillator::setFrequency(double freq, double sampleRate)
{
    frequency = freq;
    phaseDelta = (kTwoPi/sampleRate) * freq;
}

double WavetableOscillator::getFrequency() const
{
    return frequency;
}

void WavetableOscillator::setWavetable(const Wavetable* newWavetable) 
{
    wavetable = newWavetable;
}

void WavetableOscillator::setGain(double newGain)
{
    gain = newGain;
}