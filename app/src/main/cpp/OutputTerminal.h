//
// Created by JohnK on 11/11/2021.
//

#ifndef PATCH_MATCHER_OUTPUTTERMINAL_H
#define PATCH_MATCHER_OUTPUTTERMINAL_H
#include "Operator.h"
#include <list>


class OutputTerminal {
private:
    std::list<Operator*> outputOperators;
public:
    OutputTerminal(){};
    ~OutputTerminal(){};
    void addOperator(Operator* operatorToAdd) {outputOperators.push_back(operatorToAdd);};
    void removeOperator(Operator* operatorToRemove) {outputOperators.remove(operatorToRemove);};
    inline float getNextSample() const noexcept {
        float currentSample {0};
        for (const auto &outputOperator : outputOperators)
            currentSample += outputOperator->getNextSample();
        return currentSample;
    }
};


#endif //PATCH_MATCHER_OUTPUTTERMINAL_H
