//
// Created by JohnK on 2/13/2022.
//

#include "TargetGenerator.h"

TargetGenerator::TargetGenerator(float fMaxFreq, float fMaxGain) :
    m_fMaxFreq(fMaxFreq),
    m_fMaxGain(fMaxGain)
{
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
    m_pOperator1Parameters.fFreq = 440.0f;
    m_pOperator1Parameters.fGain = m_fMaxGain;
    m_pOperator1Parameters.fFeedback = 0.0f;
    m_pOperator1Parameters.operatorIds.push_back(0);

    m_pOperator2Parameters.fFreq = 220.0f;
    m_pOperator2Parameters.fGain = m_fMaxGain / 2.0f;
    m_pOperator2Parameters.fFeedback = 0.5f;
    m_pOperator2Parameters.operatorIds.push_back(1);
}
