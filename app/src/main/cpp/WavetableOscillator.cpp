//
// Created by JohnK on 10/12/2021.
//

#include "WavetableOscillator.h"
WavetableOscillator::WavetableOscillator(const Wavetable &wavetableToUse) : wavetable{wavetableToUse}, tableSize{wavetableToUse.get_size()}
{
}

WavetableOscillator::~WavetableOscillator()
{
}

void WavetableOscillator::setFrequency(float frequency, float sampleRate)
{
    float tableSizeOverSampleRate = (float)tableSize / sampleRate;
    tableDelta = frequency * tableSizeOverSampleRate;
}

void WavetableOscillator::print()
{
    std::ofstream out_file{};
    out_file.open("WavetableOscillator.csv");
    if (out_file){
        int numtimes{1000};
        while(numtimes--){
            out_file << getNextSample() << std::endl;
        }
    }
    out_file.close();

}