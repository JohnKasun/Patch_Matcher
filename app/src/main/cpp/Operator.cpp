//
// Created by JohnK on 11/4/2021.
//

#include "Operator.h"

int Operator::numOperators = 0;

Operator::Operator(const Wavetable* wavetable) :
    WavetableOscillator(wavetable),
    RADIANS_TO_INDEX(wavetable->get_size()/(kTwoPi)),
    m_bHasBeenGenerated(false),
    m_cModOperatorsIn(5),
    m_cModOperatorsOut(5)
{
    numOperators++;
}

Operator::~Operator()
{
    numOperators--;
}

void Operator::registerModulator(Operator *operatorToAdd)
{
    //modOperatorsIn.push_back(operatorToAdd);
    m_cModOperatorsIn.push_back(operatorToAdd);
}

void Operator::removeModulator(Operator *operatorToRemove)
{
    //modOperatorsIn.remove(operatorToRemove);
    m_cModOperatorsIn.remove(operatorToRemove);
}

void Operator::setFeedbackGain(float newFeedbackGain)
{
    feedbackGain = newFeedbackGain;
}

void Operator::connectTo(Operator *operatorToModulate)
{
    operatorToModulate->registerModulator(this);
    //modOperatorsOut.push_back(operatorToModulate);
    m_cModOperatorsOut.push_back(operatorToModulate);
}

void Operator::connectTo(OutputTerminal *outputTerminal)
{
    outputTerminal->addOperator(this);
}

void Operator::disconnectFrom(Operator *operatorToDisconnect)
{
    operatorToDisconnect->removeModulator(this);
    //modOperatorsOut.remove(operatorToDisconnect);
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

int Operator::getNumOperators()
{
    return numOperators;
}

//=========================================

OutputTerminal::OutputTerminal() :
    m_cOutputOperators(6),
    m_fGainNorm(0.0f),
    m_fCurrentSample(0.0f)
{

}

OutputTerminal::~OutputTerminal()
{

}

void OutputTerminal::addOperator(Operator* operatorToAdd)
{
    //outputOperators.push_back(operatorToAdd);
    m_cOutputOperators.push_back(operatorToAdd);
    updateGainNorm();
};

void OutputTerminal::removeOperator(Operator* operatorToRemove)
{
    //outputOperators.remove(operatorToRemove);
    m_cOutputOperators.remove(operatorToRemove);
    updateGainNorm();
};

void OutputTerminal::updateGainNorm()
{
    //(!outputOperators.empty()) ? m_fGainNorm = 1.0f / static_cast<float>(outputOperators.size()) : m_fGainNorm = 0.0f;
    if (m_cOutputOperators.getSize() != 0)
    {
        m_fGainNorm = 1.0f / static_cast<float>(m_cOutputOperators.getSize());
    } else
    {
        m_fGainNorm = 0.0f;
        m_fCurrentSample = 0.0f;
    }
};

