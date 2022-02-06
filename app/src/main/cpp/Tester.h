//
// Created by JohnK on 10/17/2021.
//

#ifndef PATCH_MATCHER_TESTER_H
#define PATCH_MATCHER_TESTER_H
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <functional>

#include "WavetableOscillator.h"
#include "Wavetable.h"
#include "Operator.h"
#include "SineWavetable.h"
#include "SquareWavetable.h"
#include "CustomWavetable.h"

class Operator;
class OutputTerminal;

class Tester {
private:
    static double constexpr kPI = M_PI;
    static double constexpr kTwoPi = kPI * 2;
    SineWavetable sine;
    WavetableOscillator* oscillator;
    std::ofstream diff_log;
    std::ofstream osc_log;
    std::ofstream wav_log;
    std::ofstream out_log;

    void print(const std::vector<double> &vec);
public:
    Tester();
    ~Tester();

/*    void runSineDiff(int numTrials = 10, int numSamples = 100, float sampleRate = 44100);*/
    void print(Operator& osc, int numSamples = 100);
    void print(OutputTerminal& output, int numSamples = 100);
/*    void print(Wavetable& wavetable);*/

};


#endif //PATCH_MATCHER_TESTER_H
