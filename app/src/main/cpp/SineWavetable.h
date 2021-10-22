//
// Created by JohnK on 10/15/2021.
//

#ifndef PATCH_MATCHER_SINEWAVETABLE_H
#define PATCH_MATCHER_SINEWAVETABLE_H
#include "Wavetable.h"


class SineWavetable : public Wavetable {
public:

    SineWavetable();
    virtual ~SineWavetable() = default;

    virtual void generate() override;
};


#endif //PATCH_MATCHER_SINEWAVETABLE_H
