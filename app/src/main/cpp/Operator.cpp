//
// Created by JohnK on 11/4/2021.
//

#include "Operator.h"

int Operator::numOperators = 0;

Operator::Operator(const Wavetable* wavetable)
    : WavetableOscillator(wavetable), feedbackOn(false), feedbackGain(0.0f),
        RADIANS_TO_INDEX(wavetable->get_size()/(kTwoPi)),
        numModulating{0}, counterGeneration{numModulating}, 
        shouldGenerate{true}
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

void Operator::setFeedbackGain(double newFeedbackGain)
{
    feedbackGain = newFeedbackGain;
}

void Operator::connectTo(Operator *operatorToModulate)
{
    if (operatorToModulate == this)
        enableFeedback(true);
    else {
        operatorToModulate->registerModulator(this);
        numModulating++;
        counterGeneration++;
    }
}

void Operator::connectTo(OutputTerminal *outputTerminal)
{
    numModulating++;
    counterGeneration++;
    outputTerminal->addOperator(this);
}

void Operator::disconnectFrom(Operator *operatorToDisconnect)
{
    if (operatorToDisconnect == this)
        enableFeedback(false);
    else {
        operatorToDisconnect->removeModulator(this);
        numModulating--;
        counterGeneration--;
    }

}

void Operator::disconnectFrom(OutputTerminal *outputTerminal)
{
    numModulating--;
    counterGeneration--;
    outputTerminal->removeOperator(this);
}

int Operator::getNumOperators()
{
    return numOperators;
}
