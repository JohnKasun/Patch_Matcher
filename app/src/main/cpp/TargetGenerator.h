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
#include "Wavetable.h"

struct Parameters
{
    Parameters(){};
    Parameters(float freq, float gain, float feedback, Wavetable::Wavetable_t waveType, std::set<int> ids) :
        fFreq(freq), fGain(gain), fFeedback(feedback), eWaveType(waveType), operatorIds(ids) {};
    float fFreq = 0;
    float fGain = 0;
    float fFeedback = 0;
    Wavetable::Wavetable_t eWaveType = Wavetable::Wavetable_t::kSine;
    std::set<int> operatorIds {};
    void reset()
    {
        fFreq = 0;
        fGain = 0;
        fFeedback = 0;
        eWaveType = Wavetable::kSine;
        operatorIds.clear();
    }
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

protected:

    float m_fMaxFreq;
    float m_fMaxGain;
    Parameters m_pOperator1Parameters;
    Parameters m_pOperator2Parameters;
    Parameters m_pOperator3Parameters;
    Parameters m_pOperator4Parameters;
    Parameters m_pOperator5Parameters;
    Parameters m_pOperator6Parameters;
    ConnectionSetup m_pConnectionSetup;

    Algorithm generateAlgorithm();
    float genRandParam(float lowerBound, float upperBound, bool norm = false) const;
    float genMultiple(float fFundFreq, int iLowestMultiple, int iHighestMultiple) const;
    int getRandBetween(std::vector<int>&&) const;

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
