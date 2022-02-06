//
// Created by JohnK on 11/4/2021.
//

#ifndef PATCH_MATCHER_OPERATOR_H
#define PATCH_MATCHER_OPERATOR_H
#include "Tester.h"
#include "WavetableOscillator.h"
#include "COperatorList.h"
#include <math.h>

class OutputTerminal;
class COperatorList;

class Operator : public WavetableOscillator {
    friend class Tester;
private:
    static int constexpr s_iMaxModOperators = 5;
    COperatorList m_cModOperatorsIn;
    COperatorList m_cModOperatorsOut;
    float m_fFeedbackGain;
    float RADIANS_TO_INDEX;
    bool m_bHasBeenGenerated;
    bool m_bIsCurrentlyProcessing;
    
    inline float modulatePhase(float phase) noexcept
    {
        if (!m_bIsCurrentlyProcessing)
        {
            m_bIsCurrentlyProcessing = true;
            for (int i = 0; i < m_cModOperatorsIn.getSize(); i++)
                phase += m_cModOperatorsIn.get(i)->getNextSample();
        }
        phase += m_fFeedbackGain * m_fCurrentSample;
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
        if(!m_bHasBeenGenerated)
        {
            float instanteousPhase = modulatePhase(m_fAccumulatedPhase);
            instanteousPhase = fmod(instanteousPhase, kTwoPi);
            while (instanteousPhase<0) instanteousPhase += kTwoPi;

            float currentIndex = (RADIANS_TO_INDEX) * instanteousPhase;
            int indexBelow = (int) currentIndex;
            int indexAbove = indexBelow + 1;
            if (indexAbove >= m_iTableSize)
                indexAbove = 0;

            float fracAbove = currentIndex - indexBelow;
            float fracBelow = 1.0 - fracAbove;
            m_fCurrentSample = m_fGain * ((fracBelow * m_pWavetable->at(indexBelow)) + (fracAbove * m_pWavetable->at(indexAbove)));

            if (!m_bHasBeenGenerated)
            {
                m_fAccumulatedPhase += m_fPhaseDelta;
                m_fAccumulatedPhase = fmod(m_fAccumulatedPhase, kTwoPi);
            }
            m_bHasBeenGenerated = true;
        }
        m_bIsCurrentlyProcessing = false;
        return m_fCurrentSample;
    }
};

class OutputTerminal {
    friend class Operator;
    friend class Tester;
private:

    static int constexpr s_iMaxOutputOperators = 6;
    COperatorList m_cOutputOperators;
    float m_fGainNorm;

    void addOperator(Operator* operatorToAdd);
    void removeOperator(Operator* operatorToRemove);
    void updateGainNorm();

public:

    OutputTerminal();
    ~OutputTerminal();
    inline float getNextSample() noexcept
    {
        float fCurrentSample = 0.0f;
        for (int i = 0; i < m_cOutputOperators.getSize(); i++)
            fCurrentSample += m_cOutputOperators.get(i)->getNextSample();
        return m_fGainNorm * fCurrentSample;
    }
};



#endif //PATCH_MATCHER_OPERATOR_H
