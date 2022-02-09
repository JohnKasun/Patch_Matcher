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

#include "Operator.h"
#include "Wavetable.h"

class Operator;
class OutputTerminal;

class Tester {
private:
    static double constexpr kPI = M_PI;
    static double constexpr kTwoPi = kPI * 2;
    std::ofstream diff_log;
    std::ofstream osc_log;
    std::ofstream wav_log;
    std::ofstream out_log;

public:
    Tester();
    ~Tester();

    void print(Operator& osc, int numSamples = 100);
    void print(OutputTerminal& output, int numSamples = 100);
    void print(Wavetable& wavetable);

};


#endif //PATCH_MATCHER_TESTER_H
