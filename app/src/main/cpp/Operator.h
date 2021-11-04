//
// Created by JohnK on 11/4/2021.
//

#ifndef PATCH_MATCHER_OPERATOR_H
#define PATCH_MATCHER_OPERATOR_H
#include "WavetableOscillator.h"
#include "Wavetable.h"
#include <vector>


class Operator : public WavetableOscillator {
private:
    static int numOperators;
    std::vector<Operator*> modOperators;
    bool feedbackOn;

    inline void modulate(float &currentIndex) noexcept
    {
        for (const Operator* modOperator : modOperators)
            currentIndex += modOperator->getCurrentSample();
    }
public:
    Operator(const Wavetable* wavetable);
    virtual ~Operator();
    void enableFeedback(bool shouldEnable);
    void registerModulator(Operator *operatorToAdd);
    void connectTo(Operator *operatorToModulate);
    virtual inline void generateNextSample() noexcept override
    {
        int indexBelow = (int) currentIndex;
        int indexAbove = indexBelow + 1;
        if (indexAbove >= tableSize)
            indexAbove = 0;

        float fracAbove = currentIndex - indexBelow;
        float fracBelow = 1.0 - fracAbove;

        float nextSample = (fracBelow * wavetable->at(indexBelow)) + (fracAbove * wavetable->at(indexAbove));

        currentIndex += tableDelta;
        if (!modOperators.empty()) modulate(currentIndex);
        while(currentIndex >= (float)tableSize)
            currentIndex -= tableSize;

        currentSample = gain * nextSample;
    }

    static int getNumOperators();
};


#endif //PATCH_MATCHER_OPERATOR_H
