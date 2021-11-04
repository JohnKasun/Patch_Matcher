//
// Created by JohnK on 11/4/2021.
//

#include "Operator.h"

int Operator::numOperators = 0;

Operator::Operator(const Wavetable* wavetable) : WavetableOscillator(wavetable), feedbackOn(false)
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

void Operator::connectTo(Operator *operatorToModulate)
{
    if (operatorToModulate == this)
        enableFeedback(true);
    else
        operatorToModulate->registerModulator(this);
}

int Operator::getNumOperators()
{
    return numOperators;
}
