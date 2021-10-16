//
// Created by JohnK on 10/15/2021.
//

#include "SquareWavetable.h"
SquareWavetable::SquareWavetable() : Wavetable()
{
}

void SquareWavetable::generate()
{
    for (int i {0}; i < size; i++){
        float sample{};
        if (i < size/2)
            sample = 1.0f;
        else
            sample = -1.0f;
        table[i] = sample;
    }
}