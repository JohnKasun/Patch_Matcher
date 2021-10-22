//
// Created by JohnK on 10/15/2021.
//

#ifndef CUSTOMWAVETABLE_H
#define CUSTOMWAVETABLE_H
#include "Wavetable.h"

class CustomWavetable : public Wavetable
{
private:
    std::function<float(double)> patch;
public:
    CustomWavetable(std::function<float(double)> patch = [](double){return -1;});
    virtual ~CustomWavetable();

    virtual bool setPatch(std::function<float(double)> new_patch) override;
    virtual void generate() override;
};

#endif // CUSTOMWAVETABLE_H
