//
// Created by JohnK on 10/15/2021.
//

#include "SineWavetable.h"
SineWavetable::SineWavetable() : Wavetable()
{}

void SineWavetable::generate()
{
    auto angleDelta = kTwoPi / (double)size;
    auto currentAngle = 0.0;

    for (int i = 0; i < size; ++i)
    {
        table[i] = sinf(currentAngle);
        currentAngle += angleDelta;
    }
}