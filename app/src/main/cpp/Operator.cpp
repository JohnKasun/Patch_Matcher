//
// Created by JohnK on 11/4/2021.
//

#include "Operator.h"
//=====================================================
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


//=====================================================

//=====================================================
Operator::Operator(const Wavetable* wavetable) :
    WavetableOscillator(wavetable),
    m_fFeedbackGain(0.0f),
    RADIANS_TO_INDEX(wavetable->get_size()/(kTwoPi)),
    m_bHasBeenGenerated(false),
    m_bIsCurrentlyProcessing(false)
{

}

Operator::~Operator()
{

}
void Operator::registerModulator(Operator *operatorToAdd)
{
    m_cModOperatorsIn.insert(operatorToAdd);
}

void Operator::removeModulator(Operator *operatorToRemove)
{
    m_cModOperatorsIn.erase(operatorToRemove);
}

void Operator::setFeedbackGain(float newFeedbackGain)
{
    m_fFeedbackGain = newFeedbackGain;
}

void Operator::connectTo(Operator *operatorToModulate)
{
    operatorToModulate->registerModulator(this);
    m_cModOperatorsOut.insert(operatorToModulate);
}

void Operator::connectTo(OutputTerminal *outputTerminal)
{
    outputTerminal->addOperator(this);
}

void Operator::disconnectFrom(Operator *operatorToDisconnect)
{
    operatorToDisconnect->removeModulator(this);
    m_cModOperatorsOut.erase(operatorToDisconnect);
}

void Operator::disconnectFrom(OutputTerminal *outputTerminal)
{
    outputTerminal->removeOperator(this);
}

void Operator::resetGeneration()
{
    if (m_bHasBeenGenerated)
    {
        m_bHasBeenGenerated = false;
        for (Operator* op : m_cModOperatorsIn)
            op->resetGeneration();
    }

}

void Operator::reset()
{
    resetGeneration();
    setFrequency(0.0f);
    setGain(0.0f);
    setFeedbackGain(0.0f);
    m_fAccumulatedPhase = 0.0f;
    m_cModOperatorsIn.clear();
    m_cModOperatorsOut.clear();
}

//=========================================

OutputTerminal::OutputTerminal() :
    m_fGainScaling(0.0f)
{

}

OutputTerminal::~OutputTerminal()
{

}

void OutputTerminal::addOperator(Operator* operatorToAdd)
{
    m_cOutputOperators.insert(operatorToAdd);
    updateGainScaling();
};

void OutputTerminal::removeOperator(Operator* operatorToRemove)
{
    m_cOutputOperators.erase(operatorToRemove);
    updateGainScaling();
};

void OutputTerminal::updateGainScaling()
{
    float fGainNorm = 0.0f;
    if (!m_cOutputOperators.empty())
    {
        fGainNorm = 1.0f / static_cast<float>(m_cOutputOperators.size());
    }
    m_fGainScaling = fGainNorm * s_fMaxGainScaling;
}

void OutputTerminal::reset()
{
    m_cOutputOperators.clear();
};



