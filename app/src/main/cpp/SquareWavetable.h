//
// Created by JohnK on 10/15/2021.
//

#ifndef SQUAREWAVETABLE_H
#define SQUAREWAVETABLE_H
#include "Wavetable.h"

class SquareWavetable : public Wavetable
{
public:
    SquareWavetable();
    ~SquareWavetable() = default;

    virtual void generate() override;

};

#endif // SQUAREWAVETABLE_H
