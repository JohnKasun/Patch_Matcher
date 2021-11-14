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