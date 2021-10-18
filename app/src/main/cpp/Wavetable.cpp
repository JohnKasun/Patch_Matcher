//
// Created by JohnK on 10/12/2021.
//

#include "Wavetable.h"

Wavetable::Wavetable() : table{}
{}

int Wavetable::get_size() const
{
    return size;
}

float Wavetable::operator[](int index) const
{
    return table[index];
};

bool Wavetable::setPatch(std::function<float(double)>)
{
    return false;
}