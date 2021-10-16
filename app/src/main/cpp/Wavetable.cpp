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

void Wavetable::print() const
{
    std::ofstream out_file{};
    out_file.open("Wavetable.csv");
    if (out_file){
        for (int i {0}; i < size; i++)
            out_file << table[i] << std::endl;
    }
    out_file.close();
}

bool Wavetable::setPatch(std::function<float(double)>)
{
    return false;
}