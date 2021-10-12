//
// Created by JohnK on 10/12/2021.
//

#include "Wavetable.h"

Wavetable::Wavetable(int size)
    : size(size), table(nullptr),
      patch( [](double currentAngle){ return sinf(currentAngle);} )
{
    table = new float[size]{};
}

Wavetable::~Wavetable()
{
    delete[] table;
}

void Wavetable::generate()
{
    auto angleDelta = kTwoPi / (double)(size - 1);
    auto currentAngle = 0.0;

    for (unsigned i = 0; i < size; ++i)
    {
        table[i] = patch(currentAngle);
        currentAngle += angleDelta;
    }
}

unsigned Wavetable::get_size() const
{
    return size;
}

float Wavetable::operator[](int index) const
{
    return table[index];
};

void Wavetable::setPatch(std::function<float(double)> new_patch)
{
    patch = new_patch;
}