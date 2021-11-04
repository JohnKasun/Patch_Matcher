//
// Created by JohnK on 10/17/2021.
//

#ifndef PATCH_MATCHER_TESTER_H
#define PATCH_MATCHER_TESTER_H
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <functional>

#include "WavetableOscillator.h"
#include "Wavetable.h"
#include "Operator.h"
#include "SineWavetable.h"
#include "SquareWavetable.h"
#include "CustomWavetable.h"


class Tester {
private:
    static float constexpr kPI = M_PI;
    static float constexpr kTwoPi = kPI * 2;
    SineWavetable sine;
    WavetableOscillator* oscillator;
    std::ofstream diff_log;
    std::ofstream osc_log;
    std::ofstream wav_log;

    void print(const std::vector<float> &vec);
public:
    Tester();
    ~Tester();

    void runSineDiff(int numTrials = 10, int numSamples = 100, float sampleRate = 44100);
    void print(WavetableOscillator& osc, int numSamples = 100);
    void print(Wavetable& wavetable);

};


#endif //PATCH_MATCHER_TESTER_H
