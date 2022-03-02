//
// Created by JohnK on 11/4/2021.
//

#ifndef PATCH_MATCHER_OPERATOR_H
#define PATCH_MATCHER_OPERATOR_H
#include "Tester.h"
#include "COperatorList.h"
#include "Wavetable.h"

#include <math.h>
#include <cmath>
#include <unordered_set>

class OutputTerminal;

class WavetableOscillator
{
protected:
    static float constexpr s_fMaxGain = 100.0f;
    static float constexpr s_fMaxGainScaling = 1.0f / s_fMaxGain;
    static float constexpr kPI = M_PI;
    static float constexpr kTwoPi = kPI * 2.0;
    static float s_fSampleRate;
    static float s_FREQ_TO_PHASEDELTA;
    static float s_PHASEDELTA_TO_FREQ;


    const Wavetable* m_pWavetable;

    int m_iTableSize;
    float m_fAccumulatedPhase;
    float m_fPhaseDelta;
    float m_fGain;
    float m_fCurrentSample;

public:
    WavetableOscillator(const Wavetable* wavetableToUse);
    virtual ~WavetableOscillator();

    void setFrequency(float freq);
    float getFrequency() const;
    void setWavetable(const Wavetable* newWavetable);
    void setGain(float newGain);
    float getGain() const;
    float getCurrentSample() const { return m_fCurrentSample; };

    virtual inline float getNextSample() noexcept = 0;
    static void setSampleRate(float fSampleRate);
};

class Operator : public WavetableOscillator {
    friend class Tester;
private:

    int m_id;
    const int s_iMaxModOperators = 5;
    std::unordered_set<Operator*> m_cModOperatorsIn;
    std::unordered_set<Operator*> m_cModOperatorsOut;
    float m_fFeedbackGain;
    float RADIANS_TO_INDEX;
    bool m_bHasBeenGenerated;
    bool m_bIsCurrentlyProcessing;
    
    inline float modulatePhase(float phase) noexcept
    {
        if (!m_bIsCurrentlyProcessing)
        {
            m_bIsCurrentlyProcessing = true;
            for (Operator* op : m_cModOperatorsIn)
                phase += op->getNextSample();
        }
        phase += m_fFeedbackGain * m_fCurrentSample;
        return phase;
    }

    void registerModulator(Operator *operatorToAdd);
    void removeModulator(Operator *operatorToRemove);
    
public:
    Operator(const Wavetable* wavetable, int id);
    virtual ~Operator();

    int getId() const { return m_id; };
    static float getMaxGain() { return s_fMaxGain; };
    float getFeedbackGain() const { return m_fFeedbackGain; };
    void setFeedbackGain(float newFeedbackGain);
    void connectTo(Operator *operatorToModulate);
    void connectTo(OutputTerminal *outputTerminal);
    void disconnectFrom(Operator *operatorToDisconnect);
    void disconnectFrom(OutputTerminal *outputTerminal);
    void resetGeneration();
    void reset();
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

    static float constexpr s_fMaxGain = 1.0f;
    static float constexpr s_fMaxGainScaling = 1.0f / s_fMaxGain;
    const int s_iMaxOutputOperators = 6;
    std::unordered_set<Operator*> m_cOutputOperators;
    float m_fGainScaling;

    void addOperator(Operator* operatorToAdd);
    void removeOperator(Operator* operatorToRemove);
    void updateGainScaling();

public:

    OutputTerminal();
    ~OutputTerminal();
    void reset();
    inline float getNextSample() noexcept
    {
        float fCurrentSample = 0.0f;
        for (Operator* op : m_cOutputOperators)
            fCurrentSample += op->getNextSample();
        for (Operator* op : m_cOutputOperators)
            op->resetGeneration();
        return m_fGainScaling * fCurrentSample;
    }
};



#endif //PATCH_MATCHER_OPERATOR_H
