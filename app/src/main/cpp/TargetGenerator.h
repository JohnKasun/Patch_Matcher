//
// Created by JohnK on 2/13/2022.
//

#ifndef PATCH_MATCHER_TARGETGENERATOR_H
#define PATCH_MATCHER_TARGETGENERATOR_H
#include <vector>
#include <list>
#include <set>
#include <stdlib.h>
#include <time.h>

struct Parameters
{
    float fFreq = 0;
    float fGain = 0;
    float fFeedback = 0;
    std::set<int> operatorIds;
};

struct Algorithm
{
    std::set<int> iOperator1Connections;
    std::set<int> iOperator2Connections;
    std::set<int> iOperator3Connections;
    std::set<int> iOperator4Connections;
};

struct ConnectionSetup
{
    Algorithm algorithm;
    int iNumActiveOperators;
};

class TargetGenerator {
public:
    TargetGenerator() { srand(time(0));};

    void setMaxFrequency(float fMaxFreq) { m_fMaxFreq = fMaxFreq; };
    void setMaxGain(float fMaxGain) { m_fMaxGain = fMaxGain; };
    void generateParameters();
    Parameters getOperatorParameters(int iOperator) const;
    ConnectionSetup getConnectionSetup() const;

private:

    float m_fMaxFreq;
    float m_fMaxGain;
    Parameters m_pOperator1Parameters;
    Parameters m_pOperator2Parameters;
    Parameters m_pOperator3Parameters;
    Parameters m_pOperator4Parameters;
    ConnectionSetup m_pConnectionSetup;

    Algorithm generateAlgorithm();
    float genRandParam(float lowerBound, float upperBound, bool norm = false) const;
    float genMultiple(float fFundFreq, int iLowestMultiple, int iHighestMultiple) const;

    const Algorithm m_sAlgorithm1 = {
            std::set<int>{0},
            std::set<int>{1},
            std::set<int>{2},
            std::set<int>{3}
    };

    const Algorithm m_sAlgorithm2 = {
            std::set<int>{0},
            std::set<int>{1},
            std::set<int>{2},
            std::set<int>{2}
    };

    const Algorithm m_sAlgorithm3 = {
            std::set<int>{0},
            std::set<int>{1},
            std::set<int>{1},
            std::set<int>{2}
    };

    const Algorithm m_sAlgorithm4 = {
            std::set<int>{0},
            std::set<int>{0},
            std::set<int>{1},
            std::set<int>{2}
    };

    const Algorithm m_sAlgorithm5 = {
            std::set<int>{0},
            std::set<int>{0},
            std::set<int>{0},
            std::set<int>{1,2,3}
    };


};


#endif //PATCH_MATCHER_TARGETGENERATOR_H
