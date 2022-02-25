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

struct Algorithm
{
    std::vector<int> iOperator1Connections;
    std::vector<int> iOperator2Connections;
    std::vector<int> iOperator3Connections;
    std::vector<int> iOperator4Connections;
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
    Parameters m_pOperator4Parameters;

    void generateParameters();
    void generateAlgorithms();
    Algorithm getAlgorithm() const;
    float genRandParam(float lowerBound, float upperBound, bool norm = false) const;
    float genRandEvenParam(float lowerbound, float upperBound) const;
    float genMultiple(float fFundFreq, int iLowestMultiple, int iHighestMultiple) const;

    const Algorithm m_sAlgorithm1 = {
            std::vector<int>{0},
            std::vector<int>{1},
            std::vector<int>{2},
            std::vector<int>{3}
    };

    const Algorithm m_sAlgorithm2 = {
            std::vector<int>{0},
            std::vector<int>{1},
            std::vector<int>{2},
            std::vector<int>{2}
    };

    const Algorithm m_sAlgorithm3 = {
            std::vector<int>{0},
            std::vector<int>{1},
            std::vector<int>{1},
            std::vector<int>{2}
    };

    const Algorithm m_sAlgorithm4 = {
            std::vector<int>{0},
            std::vector<int>{0},
            std::vector<int>{1},
            std::vector<int>{2}
    };

    const Algorithm m_sAlgorithm5 = {
            std::vector<int>{0},
            std::vector<int>{0},
            std::vector<int>{0},
            std::vector<int>{1,2,3}
    };


};


#endif //PATCH_MATCHER_TARGETGENERATOR_H
