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
    void disconnectFrom(Operator *operatorToDisconnect);
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


#endif //PATCH_MATCHER_OPERATOR_H
