//
// Created by JohnK on 10/15/2021.
//

#include "CustomWavetable.h"
CustomWavetable::CustomWavetable(std::function<float(double)> patch) : Wavetable(), patch{patch}
{
}

CustomWavetable::~CustomWavetable()
{
}

bool CustomWavetable::setPatch(std::function<float(double)> new_patch)
{
    patch = new_patch;
    return true;
}

void CustomWavetable::generate()
{
    auto angleDelta = kTwoPi / (double)size;
    auto currentAngle = 0.0;

    for (unsigned i = 0; i < size; ++i)
    {
        table[i] = patch(currentAngle);
        currentAngle += angleDelta;
    }
}