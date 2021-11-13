//
// Created by JohnK on 11/4/2021.
//

#ifndef PATCH_MATCHER_OPERATOR_H
#define PATCH_MATCHER_OPERATOR_H
#include "Tester.h"
#include "WavetableOscillator.h"
#include "Wavetable.h"
#include <list>
#include <iostream>

class OutputTerminal;

class Operator : public WavetableOscillator {
    friend class Tester;
private:
    static int numOperators;
    std::list<Operator*> modOperators;
    bool feedbackOn;
    float RADIANS_TO_INDEX;
    int numModulating;
    int counterGeneration;
    bool shouldGenerate;
    
    inline float modulatePhase(float phase) noexcept {
        for (const auto &modOperator : modOperators)
            phase += modOperator->getNextSample();
        return phase;
    }

    inline void determineNextGeneration() noexcept {
        if (--counterGeneration <= 0){
            counterGeneration = numModulating;
            shouldGenerate = true;
        } else
            shouldGenerate = false;
    }

    void enableFeedback(bool shouldEnable);
    void registerModulator(Operator *operatorToAdd);
    void removeModulator(Operator *operatorToRemove);
    
public:
    Operator(const Wavetable* wavetable);
    virtual ~Operator();
    void connectTo(Operator *operatorToModulate);
    void connectTo(OutputTerminal *outputTerminal);
    void disconnectFrom(Operator *operatorToDisconnect);
    void disconnectFrom(OutputTerminal *outputTerminal);
    inline float getNextSample() noexcept override
    {
        if(shouldGenerate){
            float instanteousPhase = modulatePhase(accumulatedPhase);
            instanteousPhase = fmod(instanteousPhase, kTwoPi);
            while (instanteousPhase<0) instanteousPhase += kTwoPi;

            float currentIndex = (RADIANS_TO_INDEX) * instanteousPhase;
            int indexBelow = (int) currentIndex;
            int indexAbove = indexBelow + 1;
            if (indexAbove >= tableSize)
                indexAbove = 0;

            float fracAbove = currentIndex - indexBelow;
            float fracBelow = 1.0 - fracAbove;
            currentSample = gain * ((fracBelow * wavetable->at(indexBelow)) + (fracAbove * wavetable->at(indexAbove)));

            accumulatedPhase += phaseDelta;
            accumulatedPhase = fmod(accumulatedPhase, kTwoPi);

        }
        determineNextGeneration();
        return currentSample;
    }

    static int getNumOperators();
};

class OutputTerminal {
    friend class Operator;
    friend class Tester;
private:
    std::list<Operator*> outputOperators;
    void addOperator(Operator* operatorToAdd) {outputOperators.push_back(operatorToAdd);};
    void removeOperator(Operator* operatorToRemove) {outputOperators.remove(operatorToRemove);};
public:
    OutputTerminal(){};
    ~OutputTerminal(){};
    inline float getNextSample() const noexcept {
        float currentSample {0};
        for (const auto &outputOperator : outputOperators)
            currentSample += outputOperator->getNextSample();
        return currentSample;
    }
};



#endif //PATCH_MATCHER_OPERATOR_H
