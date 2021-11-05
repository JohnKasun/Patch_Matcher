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

void WavetableOscillator::setFrequency(float freq, float sampleRate)
{
    /*frequency = freq;
    float tableSizeOverSampleRate = (float)tableSize / sampleRate;
    tableDelta = frequency * tableSizeOverSampleRate;*/
    
    frequency = freq;
    phaseDelta = (kTwoPi/sampleRate) * freq;
}

float WavetableOscillator::getFrequency() const
{
    return frequency;
}

void WavetableOscillator::setWavetable(const Wavetable* newWavetable) {
    wavetable = newWavetable;
}

void WavetableOscillator::setGain(float newGain)
{
    gain = newGain;
}