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
#include <math.h>

class OutputTerminal;

class Operator : public WavetableOscillator {
    friend class Tester;
private:
    static int numOperators;
    std::list<Operator*> modOperatorsIn;
    std::list<Operator*> modOperatorsOut;
    double feedbackGain;
    double RADIANS_TO_INDEX;
    bool m_bHasBeenGenerated;
    
    inline double modulatePhase(double phase) noexcept {
        for (const auto &modOperatorIn : modOperatorsIn)
            phase += modOperatorIn->getNextSample();
        phase += feedbackGain * currentSample;
        return phase;
    }

    void enableFeedback(bool shouldEnable);
    void registerModulator(Operator *operatorToAdd);
    void removeModulator(Operator *operatorToRemove);
    
public:
    Operator(const Wavetable* wavetable);
    virtual ~Operator();
    void setFeedbackGain(double newFeedbackGain);
    void connectTo(Operator *operatorToModulate);
    void connectTo(OutputTerminal *outputTerminal);
    void disconnectFrom(Operator *operatorToDisconnect);
    void disconnectFrom(OutputTerminal *outputTerminal);
    void reset();
    void resetGeneration();
    inline double getNextSample() noexcept override
    {
        if(!m_bHasBeenGenerated){
            double instanteousPhase = modulatePhase(accumulatedPhase);
            instanteousPhase = fmod(instanteousPhase, kTwoPi);
            while (instanteousPhase<0) instanteousPhase += kTwoPi;

            double currentIndex = (RADIANS_TO_INDEX) * instanteousPhase;
            int indexBelow = (int) currentIndex;
            int indexAbove = indexBelow + 1;
            if (indexAbove >= tableSize)
                indexAbove = 0;

            double fracAbove = currentIndex - indexBelow;
            double fracBelow = 1.0 - fracAbove;
            currentSample = gain * ((fracBelow * wavetable->at(indexBelow)) + (fracAbove * wavetable->at(indexAbove)));

            accumulatedPhase += phaseDelta;
            accumulatedPhase = fmod(accumulatedPhase, kTwoPi);

            m_bHasBeenGenerated = true;
        }
        return currentSample;
    }

    static int getNumOperators();
};

class OutputTerminal {
    friend class Operator;
    friend class Tester;
private:
    std::list<Operator*> outputOperators;
    void addOperator(Operator* operatorToAdd) {outputOperators.push_back(operatorToAdd); updateGainNorm();};
    void removeOperator(Operator* operatorToRemove) {outputOperators.remove(operatorToRemove); updateGainNorm();};
    double gainNorm;
    void updateGainNorm() { (!outputOperators.empty()) ? gainNorm = 1.0 / outputOperators.size() : gainNorm = 0.0; };
public:
    OutputTerminal(){};
    ~OutputTerminal(){};
    inline double getNextSample() const noexcept {
        double currentSample {0.0};
        for (const auto &outputOperator : outputOperators)
            currentSample += outputOperator->getNextSample();
        return gainNorm * currentSample;
    }
};



#endif //PATCH_MATCHER_OPERATOR_H
