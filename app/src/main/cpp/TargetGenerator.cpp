//
// Created by JohnK on 2/13/2022.
//

#include "TargetGenerator.h"


Parameters TargetGenerator::getOperatorParameters(int iOperator) const {
    switch (iOperator)
    {
        case 1:
            return m_pOperator1Parameters;
        case 2:
            return m_pOperator2Parameters;
        case 3:
            return m_pOperator3Parameters;
        case 4:
            return m_pOperator4Parameters;
    }
}

void TargetGenerator::generateParameters()
{
    float fFundFreq = genRandParam(50.0f, 200.0f);
    Algorithm algorithmToUse = getAlgorithm();

    m_pOperator1Parameters.fFreq = genMultiple(fFundFreq, 1, 4);
    m_pOperator1Parameters.fGain = m_fMaxGain;
    m_pOperator1Parameters.fFeedback = genRandParam(0.0f, 100.0f, true);
    m_pOperator1Parameters.operatorIds = algorithmToUse.iOperator1Connections;

    m_pOperator2Parameters.fFreq = genMultiple(200, 1, 9);
    m_pOperator2Parameters.fGain = genRandParam(0.0f, m_fMaxGain);
    m_pOperator2Parameters.fFeedback = genRandParam(0.0f, 100.0f, true);
    m_pOperator2Parameters.operatorIds = algorithmToUse.iOperator2Connections;

    m_pOperator3Parameters.fFreq = genMultiple(fFundFreq, 1, 9);
    m_pOperator3Parameters.fGain = genRandParam(0.0f, m_fMaxGain);
    m_pOperator3Parameters.fFeedback = genRandParam(0.0f, 100.0f, true);
    m_pOperator3Parameters.operatorIds = algorithmToUse.iOperator3Connections;

    m_pOperator4Parameters.fFreq = genMultiple(fFundFreq, 1, 9);
    m_pOperator4Parameters.fGain = genRandParam(0.0f, m_fMaxGain);
    m_pOperator4Parameters.fFeedback = genRandParam(0.0f, 100.0f, true);
    m_pOperator4Parameters.operatorIds = algorithmToUse.iOperator4Connections;

}

float TargetGenerator::genRandParam(float fLowerBound, float fUpperBound, bool norm) const {
    float fRandNum = fmod(rand(),fUpperBound-fLowerBound+1)+fLowerBound;
    if (norm)
        fRandNum /= fUpperBound;
    return fRandNum;
}

float
TargetGenerator::genMultiple(float fFundFreq, int iLowestMultiple, int iHighestMultiple) const {
    int fRandNum = rand() % (iHighestMultiple - iLowestMultiple + 1) + iLowestMultiple;
    return fFundFreq * static_cast<float>(fRandNum);
}

Algorithm TargetGenerator::getAlgorithm() const {
    int sAlgorithmToUse = static_cast<int>(genRandParam(1,5));
    switch (sAlgorithmToUse)
    {
        case 1:
            return m_sAlgorithm1;
        case 2:
            return m_sAlgorithm2;
        case 3:
            return m_sAlgorithm3;
        case 4:
            return m_sAlgorithm4;
        default:
            return m_sAlgorithm5;
    }
}


