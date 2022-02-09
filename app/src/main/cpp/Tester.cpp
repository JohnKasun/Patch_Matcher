#include "Tester.h"

Tester::Tester()
{
    std::srand(time(0));
    diff_log.open("log_WavetableOscillatorDiffs.csv");
    osc_log.open("log_WavetableOscillators.csv");
    wav_log.open("log_Wavetables.csv");
    out_log.open("log_OutputTerminal.csv");
}

void Tester::print(Operator& osc, int numSamples)
{
    if (osc_log){

        for (int sample {0}; sample < numSamples - 1; sample++)
        {
            osc_log << osc.getNextSample() << ",";
        }
        osc_log << osc.getNextSample();
        osc_log << std::endl;
        std::cout << "done" << std::endl;
    }
}

void Tester::print(OutputTerminal &output, int numSamples)
{
    if (out_log){

        for (int sample {0}; sample < numSamples - 1; sample++)
        {
            out_log << output.getNextSample() << ",";
        }
        out_log << output.getNextSample();
        out_log << std::endl;
        std::cout << "done" << std::endl;
    }
}

void Tester::print(Wavetable& wavetable)
{
    static int numTables {0};
    if (wav_log){
        for (int sample {0}; sample < wavetable.get_size() - 1; sample++)
            wav_log << wavetable[sample] << ",";
        wav_log << wavetable[wavetable.get_size()-1];
        wav_log << std::endl;
    }
}

Tester::~Tester()
{
    diff_log.close();
    osc_log.close();
    wav_log.close();
    out_log.close();
}


