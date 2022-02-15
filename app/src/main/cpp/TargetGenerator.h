//
// Created by JohnK on 2/13/2022.
//

#ifndef PATCH_MATCHER_TARGETGENERATOR_H
#define PATCH_MATCHER_TARGETGENERATOR_H
#include <vector>
#include <stdlib.h>
#include <time.h>

struct Parameters
{
    float fFreq;
    float fGain;
    float fFeedback;
    std::vector<int> operatorIds;
};

class TargetGenerator {
public:
    TargetGenerator(float fMaxFreq, float fMaxGain);
    ~TargetGenerator();

    Parameters getOperatorParameters(int iOperator) const;

private:

    float m_fMaxFreq;
    float m_fMaxGain;
    Parameters m_pOperator1Parameters;
    Parameters m_pOperator2Parameters;
    Parameters m_pOperator3Parameters;

    void generateParameters();
    float genRandParam(float lowerBound, float upperBound, bool norm = false) const;
    float genRandEvenParam(float lowerbound, float upperBound) const;

};


#endif //PATCH_MATCHER_TARGETGENERATOR_H
