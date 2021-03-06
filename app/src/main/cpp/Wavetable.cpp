//
// Created by JohnK on 10/12/2021.
//

#include "Wavetable.h"

//=======================================================
Wavetable::Wavetable() : table{}
{ }

int Wavetable::get_size() const
{
    return size;
}

float Wavetable::operator[](int index) const
{
    return table[index];
};

float Wavetable::at(int index) const
{
    //Add bounds checking?
    return table[index];
}

bool Wavetable::setPatch(std::function<float(float)>)
{
    return false;
}

void Wavetable::normalize()
{
    float fMaxValue{0};
    for (int i = 0; i < size; i++)
    {
        float fCurrentValue = table[i];
        if (abs(fCurrentValue) > fMaxValue)
            fMaxValue = fCurrentValue;
    }
    for (int i = 0; i < size; i++)
    {
        table[i] = table[i] / fMaxValue;
    }

}
//=======================================================

//=======================================================
SineWavetable::SineWavetable() : Wavetable()
{
    float angleDelta = kTwoPi / (float)size;
    float currentAngle = 0.0;

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
    float angleDelta = kTwoPi / (float)size;
    float currentAngle = 0.0;

    for (int i = 0; i < size; i++)
    {
        float value {};
        for (int partial = 1; partial < s_iMaxPartials; partial++)
        {
            float coeff = (1.0f / partial) * (partial % 2);
            value += coeff * sin(partial * currentAngle);
        }
        table[i] = value;
        currentAngle += angleDelta;
    }
    normalize();
}
//=======================================================

//=======================================================
TriangleWavetable::TriangleWavetable() :Wavetable()
{
    float angleDelta = kTwoPi / (float)size;
    float currentAngle = 0.0;

    for (int i = 0; i < size; i++)
    {
        float value {};
        for (int partial = 1; partial < s_iMaxPartials; partial++)
        {
            float coeff = (1.0f/(powf(partial, 2))) * (partial % 2);
            if (partial % 4 == 3) coeff *= -1;
            value += coeff * sin(partial * currentAngle);
        }
        table[i] = value;
        currentAngle += angleDelta;
    }
    normalize();
}
//=======================================================

//=======================================================
SawtoothWavetable::SawtoothWavetable() : Wavetable()
{
    float angleDelta = kTwoPi / (float)size;
    float currentAngle = 0.0;

    for (int i = 0; i < size; i++)
    {
        float value {};
        for (int partial = 1; partial < s_iMaxPartials; partial++)
        {
            float coeff = 1.0f/(partial);
            value += coeff * sin(partial * currentAngle);
        }
        table[i] = value;
        currentAngle += angleDelta;
    }
    normalize();
}

//=======================================================

//=======================================================
CustomWavetable::CustomWavetable() : Wavetable()
{
    float angleDelta = kTwoPi / (float)size;
    float currentAngle = 0.0;

    for (int i = 0; i < size; ++i)
    {
        table[i] = (float)(sin(currentAngle) + 0.5 * sin(2.0*currentAngle) * 0.25 * sin(3.0 * currentAngle));
        currentAngle += angleDelta;
    }

    normalize();
}
//=======================================================