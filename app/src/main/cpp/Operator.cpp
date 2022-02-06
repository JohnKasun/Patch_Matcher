//
// Created by JohnK on 11/4/2021.
//

#include "Operator.h"

int Operator::numOperators = 0;

Operator::Operator(const Wavetable* wavetable) :
    WavetableOscillator(wavetable),
    feedbackGain(0.0f),
    RADIANS_TO_INDEX(wavetable->get_size()/(kTwoPi)),
    m_bHasBeenGenerated(false)
{
    numOperators++;
}

Operator::~Operator()
{
    numOperators--;
}
void Operator::registerModulator(Operator *operatorToAdd)
{
    modOperatorsIn.push_back(operatorToAdd);
}

void Operator::removeModulator(Operator *operatorToRemove)
{
    modOperatorsIn.remove(operatorToRemove);
}

void Operator::setFeedbackGain(double newFeedbackGain)
{
    feedbackGain = newFeedbackGain;
}

void Operator::connectTo(Operator *operatorToModulate)
{
    operatorToModulate->registerModulator(this);
    modOperatorsOut.push_back(operatorToModulate);
}

void Operator::connectTo(OutputTerminal *outputTerminal)
{
    outputTerminal->addOperator(this);
}

void Operator::disconnectFrom(Operator *operatorToDisconnect)
{
    operatorToDisconnect->removeModulator(this);
    modOperatorsOut.remove(operatorToDisconnect);
}

void Operator::disconnectFrom(OutputTerminal *outputTerminal)
{
    outputTerminal->removeOperator(this);
}

void Operator::reset()
{
    std::list<Operator*> tempIn = modOperatorsIn;
    std::list<Operator*> tempOut = modOperatorsOut;
    for (auto modOperatorIn: tempIn)
        modOperatorIn->disconnectFrom(this);
    for (auto modOperatorOut: tempOut)
        disconnectFrom(modOperatorOut);
}

void Operator::resetGeneration()
{
    m_bHasBeenGenerated = false;
}

int Operator::getNumOperators()
{
    return numOperators;
}
