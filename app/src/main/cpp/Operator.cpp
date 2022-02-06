//
// Created by JohnK on 11/4/2021.
//

#include "Operator.h"

Operator::Operator(const Wavetable* wavetable) :
    WavetableOscillator(wavetable),
    m_fFeedbackGain(0.0f),
    RADIANS_TO_INDEX(wavetable->get_size()/(kTwoPi)),
    m_bHasBeenGenerated(false),
    m_bIsCurrentlyProcessing(false),
    m_cModOperatorsIn(s_iMaxModOperators),
    m_cModOperatorsOut(s_iMaxModOperators)
{

}

Operator::~Operator()
{

}

void Operator::registerModulator(Operator *operatorToAdd)
{
    m_cModOperatorsIn.push_back(operatorToAdd);
}

void Operator::removeModulator(Operator *operatorToRemove)
{
    m_cModOperatorsIn.remove(operatorToRemove);
}

void Operator::setFeedbackGain(float newFeedbackGain)
{
    m_fFeedbackGain = newFeedbackGain;
}

void Operator::connectTo(Operator *operatorToModulate)
{
    operatorToModulate->registerModulator(this);
    m_cModOperatorsOut.push_back(operatorToModulate);
}

void Operator::connectTo(OutputTerminal *outputTerminal)
{
    outputTerminal->addOperator(this);
}

void Operator::disconnectFrom(Operator *operatorToDisconnect)
{
    operatorToDisconnect->removeModulator(this);
    m_cModOperatorsOut.remove(operatorToDisconnect);
}

void Operator::disconnectFrom(OutputTerminal *outputTerminal)
{
    outputTerminal->removeOperator(this);
}

void Operator::resetGeneration()
{
    m_bHasBeenGenerated = false;
}

//=========================================

OutputTerminal::OutputTerminal() :
    m_cOutputOperators(s_iMaxOutputOperators),
    m_fGainNorm(0.0f)
{

}

OutputTerminal::~OutputTerminal()
{

}

void OutputTerminal::addOperator(Operator* operatorToAdd)
{
    m_cOutputOperators.push_back(operatorToAdd);
    updateGainNorm();
};

void OutputTerminal::removeOperator(Operator* operatorToRemove)
{
    m_cOutputOperators.remove(operatorToRemove);
    updateGainNorm();
};

void OutputTerminal::updateGainNorm()
{
    if (m_cOutputOperators.getSize() != 0)
    {
        m_fGainNorm = 1.0f / static_cast<float>(m_cOutputOperators.getSize());
    } else
    {
        m_fGainNorm = 0.0f;
    }
};

