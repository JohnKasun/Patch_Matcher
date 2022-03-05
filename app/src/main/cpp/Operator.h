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
    static float constexpr kTwoPi = M_PI * 2.0;
    static float s_fSampleRate;
    static float s_FREQ_TO_PHASEDELTA;
    static float s_PHASEDELTA_TO_FREQ;

    const Wavetable* m_pWavetable;
    int m_iTableSize;
    float m_fAccumulatedPhase = 0.0f;
    float m_fPhaseDelta = 0.0f;
    float m_fGain = 0.0f;
    float m_fCurrentSample = 0.0f;

public:
    WavetableOscillator(const Wavetable* wavetableToUse) :
            m_pWavetable{wavetableToUse},
            m_iTableSize{wavetableToUse->get_size()} {};

    virtual ~WavetableOscillator() = default;

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
    std::unordered_set<Operator*> m_cModOperatorsIn;
    float RADIANS_TO_INDEX;
    const int s_iMaxModOperators = 5;
    float m_fFeedbackGain = 0.0f;
    bool m_bHasBeenGenerated = false;
    bool m_bIsCurrentlyProcessing = false;

    void registerModulator(Operator *operatorToAdd);
    void removeModulator(Operator *operatorToRemove);
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
    
public:
    Operator(const Wavetable* wavetable, int id) :
            WavetableOscillator(wavetable),
            m_id(id),
            RADIANS_TO_INDEX(wavetable->get_size()/(kTwoPi)){};

    virtual ~Operator() = default;

    static float getMaxGain() { return s_fMaxGain; };
    int getId() const { return m_id; };
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

    void resetPhase();
};

class OutputTerminal {
    friend class Operator;
    friend class Tester;
private:

    std::unordered_set<Operator*> m_cOutputOperators;
    static float constexpr s_fMaxGain = 1.0f;
    static float constexpr s_fMaxGainScaling = 1.0f / s_fMaxGain;
    const int s_iMaxOutputOperators = 6;
    float m_fGainScaling = 0.0f;

    void addOperator(Operator* operatorToAdd);
    void removeOperator(Operator* operatorToRemove);
    void updateGainScaling();

public:

    OutputTerminal() {};
    ~OutputTerminal() {};
    void reset();
    bool isEmpty() { return m_cOutputOperators.size() == 0; };
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
