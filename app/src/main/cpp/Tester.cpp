#include "Tester.h"

Tester::Tester()
{
    std::srand(time(0));
    diff_log.open("log_WavetableOscillatorDiffs.csv");
    osc_log.open("log_WavetableOscillators.csv");
    wav_log.open("log_Wavetables.csv");
    out_log.open("log_OutputTerminal.csv");
}

/*void Tester::runSineDiff(int numTrials, int numSamples, float sampleRate)
{
    sine.generate();

    for (auto trial {0}; trial < numTrials; ++trial){
        oscillator = new Operator(&sine);
        float randomFreq = (float)(rand()%460 + 20);
        oscillator->setFrequency(randomFreq, sampleRate);
        auto ground_func = [sampleRate, randomFreq](int n){
            float omega { kTwoPi / sampleRate * randomFreq };
            return sinf( omega * n );
        };

        std::vector<float> diff_vec;
        for (auto n {0}; n < numSamples; n++){
            oscillator->getNextSample();
            float diff_val = oscillator->getCurrentSample() - ground_func(n);
            diff_vec.push_back(diff_val);
        }
        print(diff_vec);

        delete oscillator;
    }
}*/

void Tester::print(const std::vector<double> &vec)
{
    if (diff_log){
        for (size_t i {0}; i < vec.size(); i++)
            diff_log << vec[i] << ",";
        diff_log << std::endl;
    }
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

/*void Tester::print(Wavetable& wavetable)
{
    static int numTables {0};
    if (wav_log){
        wav_log << "--" << ++numTables << "--";
        for (int sample {0}; sample < wavetable.get_size(); sample++)
            wav_log << "," << wavetable[sample];
        wav_log << std::endl;
    }
}*/

Tester::~Tester()
{
    diff_log.close();
    osc_log.close();
    wav_log.close();
    out_log.close();
}


