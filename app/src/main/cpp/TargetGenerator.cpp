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
        case 5:
            return m_pOperator5Parameters;
        default:
            return m_pOperator6Parameters;
    }
}

void TargetGenerator::generateParameters()
{

    float fFundFreq = genRandParam(50, 200);
    Algorithm algorithmToUse = m_sAlgorithm1;
    m_pConnectionSetup.algorithm = algorithmToUse;
    m_pConnectionSetup.iNumActiveOperators = 2;

    m_pOperator2Parameters.fFreq = fFundFreq;
    m_pOperator2Parameters.fGain = 100;
    m_pOperator2Parameters.fFeedback = 0;
    m_pOperator2Parameters.eWaveType = Wavetable::kSine;
    m_pOperator2Parameters.operatorIds = algorithmToUse.iOperator2Connections;

    m_pOperator1Parameters.fFreq = genMultiple(fFundFreq, 1, 4);
    m_pOperator1Parameters.fGain = 100;
    m_pOperator1Parameters.fFeedback = 0;
    m_pOperator1Parameters.eWaveType = Wavetable::kSine;
    m_pOperator1Parameters.operatorIds = algorithmToUse.iOperator1Connections;

/*    float fFundFreq = genRandParam(50.0f, 200.0f);
    Algorithm algorithmToUse = generateAlgorithm();
    m_pConnectionSetup.algorithm = algorithmToUse;
    m_pConnectionSetup.iNumActiveOperators = static_cast<int>(genRandParam(2, 4) + getRandBetween(std::vector<int>{0,0,0,0,1,1,2}));

    switch (m_pConnectionSetup.iNumActiveOperators)
    {
        case 6:
            m_pOperator6Parameters.fFreq = genRandParam(2, 4);
            m_pOperator6Parameters.fGain = m_fMaxGain;
            m_pOperator6Parameters.fFeedback = genRandParam(0.0f, 100.0f, true);
            m_pOperator6Parameters.eWaveType = static_cast<Wavetable::Wavetable_t>(getRandBetween(std::vector<int>{0,2,4}));
            m_pOperator6Parameters.operatorIds = std::set<int>{static_cast<int>(genRandParam(1,2))};
        case 5:
            m_pOperator5Parameters.fFreq = genRandParam(2, 4);
            m_pOperator5Parameters.fGain = m_fMaxGain;
            m_pOperator5Parameters.fFeedback = genRandParam(0.0f, 100.0f, true);
            m_pOperator5Parameters.eWaveType = static_cast<Wavetable::Wavetable_t>(getRandBetween(std::vector<int>{0,2,4}));
            m_pOperator5Parameters.operatorIds = std::set<int>{static_cast<int>(genRandParam(1,2))};
        case 4:
            m_pOperator4Parameters.fFreq = genMultiple(fFundFreq, 1, 9);
            m_pOperator4Parameters.fGain = genRandParam(0.0f, m_fMaxGain);
            m_pOperator4Parameters.fFeedback = genRandParam(0.0f, 100.0f, true);
            m_pOperator4Parameters.eWaveType = static_cast<Wavetable::Wavetable_t>(genRandParam(0, 4));
            m_pOperator4Parameters.operatorIds = algorithmToUse.iOperator4Connections;
        case 3:
            m_pOperator3Parameters.fFreq = genMultiple(fFundFreq, 1, 9);
            m_pOperator3Parameters.fGain = genRandParam(0.0f, m_fMaxGain);
            m_pOperator3Parameters.fFeedback = genRandParam(0.0f, 100.0f, true);
            m_pOperator3Parameters.eWaveType = static_cast<Wavetable::Wavetable_t>(genRandParam(0, 4));
            m_pOperator3Parameters.operatorIds = algorithmToUse.iOperator3Connections;
        case 2:
            m_pOperator2Parameters.fFreq = genMultiple(fFundFreq, 1, 9);
            m_pOperator2Parameters.fGain = genRandParam(0.0f, m_fMaxGain);
            m_pOperator2Parameters.fFeedback = genRandParam(0.0f, 100.0f, true);
            m_pOperator2Parameters.eWaveType = static_cast<Wavetable::Wavetable_t>(genRandParam(0, 4));
            m_pOperator2Parameters.operatorIds = algorithmToUse.iOperator2Connections;
        default:
            m_pOperator1Parameters.fFreq = genMultiple(fFundFreq, 1, 4);
            m_pOperator1Parameters.fGain = getRandBetween(std::vector<int>{50, 100});
            m_pOperator1Parameters.fFeedback = genRandParam(0.0f, 100.0f, true);
            m_pOperator1Parameters.eWaveType = static_cast<Wavetable::Wavetable_t>(genRandParam(0, 4));
            m_pOperator1Parameters.operatorIds = algorithmToUse.iOperator1Connections;
    }*/

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

Algorithm TargetGenerator::generateAlgorithm() {
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

ConnectionSetup TargetGenerator::getConnectionSetup() const {
    return m_pConnectionSetup;
}

int TargetGenerator::getRandBetween(std::vector<int> &&vec) const {
    int iRandIndex = static_cast<int>(genRandParam(0, vec.size()-1));
    return vec[iRandIndex];
}


