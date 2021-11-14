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
        double sample{};
        if (i < size/2)
            sample = 1.0;
        else
            sample = -1.0;
        table[i] = sample;
    }
}