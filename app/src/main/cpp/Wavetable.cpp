//
// Created by JohnK on 10/12/2021.
//

#include "Wavetable.h"

//=======================================================
Wavetable::Wavetable() : table{}
{}

int Wavetable::get_size() const
{
    return size;
}

double Wavetable::operator[](int index) const
{
    return table[index];
};

double Wavetable::at(int index) const
{
    //Add bounds checking?
    return table[index];
}

bool Wavetable::setPatch(std::function<double(double)>)
{
    return false;
}
//=======================================================

//=======================================================
SineWavetable::SineWavetable() : Wavetable()
{}
void SineWavetable::generate()
{
    auto angleDelta = kTwoPi / (double)size;
    auto currentAngle = 0.0;

    for (int i = 0; i < size; ++i)
    {
        table[i] = sin(currentAngle);
        currentAngle += angleDelta;
    }
}
//=======================================================

//=======================================================
SquareWavetable::SquareWavetable() : Wavetable()
{
}

void SquareWavetable::generate()
{
    int iMiddlePoint = size / 2;
    table[0] = 0.0;
    for (int i {1}; i < size; i++){
        double sample{};
        if (i < iMiddlePoint)
            sample = 1.0;
        else if (i == iMiddlePoint)
            sample = 0.0;
        else
            sample = -1.0;
        table[i] = sample;
    }
}
//=======================================================

//=======================================================
CustomWavetable::CustomWavetable(std::function<double(double)> patch) : Wavetable(), patch{patch}
{
}

CustomWavetable::~CustomWavetable()
{
}

bool CustomWavetable::setPatch(std::function<double(double)> new_patch)
{
    patch = new_patch;
    return true;
}

void CustomWavetable::generate()
{
    auto angleDelta = kTwoPi / (double)size;
    auto currentAngle = 0.0;

    for (int i = 0; i < size; ++i)
    {
        table[i] = patch(currentAngle);
        currentAngle += angleDelta;
    }
}
//=======================================================