//
// Created by JohnK on 11/4/2021.
//

#ifndef PATCH_MATCHER_OPERATOR_H
#define PATCH_MATCHER_OPERATOR_H
#include "Tester.h"
#include "WavetableOscillator.h"
#include "Wavetable.h"
#include "COperatorList.h"
#include <list>
#include <iostream>
#include <math.h>

class OutputTerminal;
class COperatorList;

class Operator : public WavetableOscillator {
    friend class Tester;
private:
    static int numOperators;
    //std::list<Operator*> modOperatorsIn;
    //std::list<Operator*> modOperatorsOut;
    COperatorList m_cModOperatorsIn;
    COperatorList m_cModOperatorsOut;
    float feedbackGain;
    float RADIANS_TO_INDEX;
    bool m_bHasBeenGenerated;
    
    inline float modulatePhase(float phase) noexcept
    {
        /*for (const auto &modOperatorIn : modOperatorsIn)
            phase += modOperatorIn->getNextSample();*/
        for (int i = 0; i < m_cModOperatorsIn.getSize(); i++)
            phase += m_cModOperatorsIn.get(i)->getNextSample();
        phase += feedbackGain * currentSample;
        return phase;
    }

    void registerModulator(Operator *operatorToAdd);
    void removeModulator(Operator *operatorToRemove);
    
public:
    Operator(const Wavetable* wavetable);
    virtual ~Operator();
    void setFeedbackGain(float newFeedbackGain);
    void connectTo(Operator *operatorToModulate);
    void connectTo(OutputTerminal *outputTerminal);
    void disconnectFrom(Operator *operatorToDisconnect);
    void disconnectFrom(OutputTerminal *outputTerminal);
    void resetGeneration();
    inline float getNextSample() noexcept override
    {
        if(!m_bHasBeenGenerated){
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

    //std::list<Operator*> outputOperators;
    COperatorList m_cOutputOperators;
    float m_fGainNorm;
    float m_fCurrentSample;

    void addOperator(Operator* operatorToAdd);
    void removeOperator(Operator* operatorToRemove);
    void updateGainNorm();

public:

    OutputTerminal();
    ~OutputTerminal();
    inline float getNextSample() noexcept
    {
        /*for (const auto &outputOperator : outputOperators)
            currentSample += outputOperator->getNextSample();*/
        for (int i = 0; i < m_cOutputOperators.getSize(); i++)
            m_fCurrentSample = m_cOutputOperators.get(i)->getNextSample();
        return m_fGainNorm * m_fCurrentSample;
    }
};



#endif //PATCH_MATCHER_OPERATOR_H
