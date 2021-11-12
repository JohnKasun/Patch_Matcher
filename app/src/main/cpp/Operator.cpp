//
// Created by JohnK on 11/4/2021.
//

#include "Operator.h"

int Operator::numOperators = 0;

Operator::Operator(const Wavetable* wavetable)
    : WavetableOscillator(wavetable), feedbackOn(false),
        RADIANS_TO_INDEX(wavetable->get_size()/(kTwoPi)),
        numModulating{0}, counterGeneration{numModulating}, shouldGenerate(true)
{
    numOperators++;
}

Operator::~Operator()
{
    numOperators--;
}

void Operator::enableFeedback(bool shouldEnable)
{
    feedbackOn = shouldEnable;
}

void Operator::registerModulator(Operator *operatorToAdd)
{
    modOperators.push_back(operatorToAdd);
}

void Operator::removeModulator(Operator *operatorToRemove)
{
    modOperators.remove(operatorToRemove);
}

void Operator::connectTo(Operator *operatorToModulate)
{
    numModulating++;
    counterGeneration++;
    if (operatorToModulate == this)
        enableFeedback(true);
    else
        operatorToModulate->registerModulator(this);
}

void Operator::connectTo(OutputTerminal *outputTerminal)
{
    outputTerminal->addOperator(this);
}

void Operator::disconnectFrom(Operator *operatorToDisconnect)
{
    numModulating--;
    counterGeneration--;
    if (operatorToDisconnect == this)
        enableFeedback(false);
    else
        operatorToDisconnect->removeModulator(this);
}

void Operator::disconnectFrom(OutputTerminal *outputTerminal)
{
    outputTerminal->removeOperator(this);
}

int Operator::getNumOperators()
{
    return numOperators;
}
