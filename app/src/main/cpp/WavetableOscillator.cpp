//
// Created by JohnK on 10/12/2021.
//

#include "WavetableOscillator.h"
WavetableOscillator::WavetableOscillator(const Wavetable* wavetableToUse) :
        m_pWavetable{wavetableToUse},
        m_iTableSize{wavetableToUse->get_size()},
        m_fAccumulatedPhase(0.0f),
        m_fPhaseDelta(0.0f),
        m_fGain(0.0f * s_fMaxGainScaling),
        m_fCurrentSample(0.0f)
{

}

WavetableOscillator::~WavetableOscillator()
{
}

void WavetableOscillator::setFrequency(float freq)
{
    m_fPhaseDelta = s_FREQ_TO_PHASEDELTA * freq;
}

float WavetableOscillator::getFrequency() const
{
    return s_PHASEDELTA_TO_FREQ * m_fPhaseDelta;
}

void WavetableOscillator::setWavetable(const Wavetable* newWavetable) 
{
    m_pWavetable = newWavetable;
}

void WavetableOscillator::setGain(float newGain)
{
    m_fGain = newGain * s_fMaxGainScaling;
}

float WavetableOscillator::getGain() const
{
    return m_fGain;
}

void WavetableOscillator::setSampleRate(float fSampleRate)
{
    s_fSampleRate = fSampleRate;
    s_FREQ_TO_PHASEDELTA = kTwoPi / s_fSampleRate;
    s_PHASEDELTA_TO_FREQ = 1.0f / kTwoPi;
}

float WavetableOscillator::s_fSampleRate = 0.0f;
float WavetableOscillator::s_FREQ_TO_PHASEDELTA = 0.0f;
float WavetableOscillator::s_PHASEDELTA_TO_FREQ = 0.0f;
