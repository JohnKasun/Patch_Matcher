//
// Created by JohnK on 10/12/2021.
//

#include "Wavetable.h"

Wavetable::Wavetable(int size)
    : size(size), table(nullptr),
      patch( [](int index){ return sinf(index);} )
{
    table = new float[size];
}

Wavetable::~Wavetable()
{
    delete[] table;
}

void Wavetable::generate()
{
    int index =
    table[index] = patch(index);
}

unsigned Wavetable::get_size() const
{
    return size;
}

float Wavetable::operator[](int index) const
{

};

void Wavetable::setPatch(std::function<float(int)> new_patch)
{
    patch = new_patch;
}