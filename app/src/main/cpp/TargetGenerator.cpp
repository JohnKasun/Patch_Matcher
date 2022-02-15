//
// Created by JohnK on 2/13/2022.
//

#include "TargetGenerator.h"

TargetGenerator::TargetGenerator(float fMaxFreq, float fMaxGain) :
    m_fMaxFreq(fMaxFreq),
    m_fMaxGain(fMaxGain)
{
    srand(time(0));
    generateParameters();
}

TargetGenerator::~TargetGenerator() {

}

Parameters TargetGenerator::getOperatorParameters(int iOperator) const {
    switch (iOperator)
    {
        case 1:
            return m_pOperator1Parameters;
        case 2:
            return m_pOperator2Parameters;
        default:
            return m_pOperator3Parameters;
    }
}

void TargetGenerator::generateParameters()
{

    m_pOperator1Parameters.fFreq = genRandEvenParam(200.0f, 5000.0f);
    m_pOperator1Parameters.fGain = m_fMaxGain;
    m_pOperator1Parameters.fFeedback = genRandParam(0.0f, 100.0f, true);
    m_pOperator1Parameters.operatorIds.push_back(0);

    m_pOperator2Parameters.fFreq = m_pOperator1Parameters.fFreq / genRandEvenParam(1.0f, 5.0f);
    m_pOperator2Parameters.fGain = genRandParam(m_fMaxGain / 2.0f, m_fMaxGain);
    m_pOperator2Parameters.fFeedback = genRandParam(0.0f, 100.0f, true);
    m_pOperator2Parameters.operatorIds.push_back(1);
}

float TargetGenerator::genRandParam(float fLowerBound, float fUpperBound, bool norm) const {
    float fRandNum = fmod(rand(),fUpperBound-fLowerBound+1)+fLowerBound;
    if (norm)
        fRandNum /= fUpperBound;
    return fRandNum;
}

float TargetGenerator::genRandEvenParam(float fLowerBound, float fUpperBound) const {
    float fRandNum = genRandParam(fLowerBound / 2.0f, fUpperBound / 2.0f) * 2.0f;
    return fRandNum;
}
