//
// Created by JohnK on 4/12/2022.
//

#ifndef PATCH_MATCHER_LEVELGENERATOR_H
#define PATCH_MATCHER_LEVELGENERATOR_H

#include "TargetGenerator.h"

struct LevelParameters{
    Parameters Operator1;
    Parameters Operator2;
    Parameters Operator3;
    Parameters Operator4;
    Parameters Operator5;
    Parameters Operator6;
};

class LevelGenerator : public TargetGenerator{

public:
    LevelGenerator();
    ~LevelGenerator();

    LevelParameters getLevelParameters(int level) const;
    LevelParameters getTutorialParameters() const;

private:

    const LevelParameters Tutorial
    {
        Parameters(440, 100, 0, Wavetable::kCustom, {0}),
        Parameters(220, 100, 0, Wavetable::kSine, {1}),
        Parameters(110, 100, 0, Wavetable::kSine, {1})
    };

    const LevelParameters Level1
    {
        Parameters(440, 100, 0, Wavetable::kSine, {0}),
        Parameters(220, 100, 0, Wavetable::kSine, {1})
    };

    const LevelParameters Level2
    {
        Parameters(620, 100, 0, Wavetable::kSine, {0}),
        Parameters(310, 100, 0, Wavetable::kSine, {1}),
        Parameters(3, 100, 0, Wavetable::kSine, {1})
    };

    const LevelParameters Level3
    {
        Parameters(330, 100, 0, Wavetable::kSine, {0}),
        Parameters(990, 100, 0, Wavetable::kSine, {1})
    };

    const LevelParameters Level4
    {
        Parameters(450, 100, 0, Wavetable::kSine, {0}),
        Parameters(300, 100, 0, Wavetable::kSine, {1})
    };

    const LevelParameters Level5
    {
        Parameters(300, 100, 0, Wavetable::kSine, {0}),
        Parameters(150, 50, 0, Wavetable::kSine, {1}),
        Parameters(75, 50, 0, Wavetable::kSine, {1})
    };

    const LevelParameters Level6
    {
        Parameters(340, 100, 0, Wavetable::kSine, {0}),
        Parameters(341, 100, 0, Wavetable::kCustom, {0})
    };

    const LevelParameters Level7
    {
        Parameters(400, 100, 0.5, Wavetable::kSine, {0}),
        Parameters(500, 50, 0, Wavetable::kSine, {1}),
        Parameters(600, 75, 0, Wavetable::kSine, {2})
    };

    const LevelParameters Level8
    {
        Parameters(250, 100, 1, Wavetable::kSine, {0}),
        Parameters(125, 100, 0, Wavetable::kSine, {1}),
        Parameters(75, 100, 0, Wavetable::kSine, {2})
    };

    const LevelParameters Level9
    {
        Parameters(560, 100, 0, Wavetable::kCustom, {0}),
        Parameters(1120, 100, 0, Wavetable::kCustom, {1}),
        Parameters(840, 100, 0.5, Wavetable::kSine, {0}),
        Parameters(210, 100, 0, Wavetable::kSine, {3})
    };

    const LevelParameters Level10
    {
        Parameters(500, 100, 0, Wavetable::kSine, {0}),
        Parameters(501, 100, 0, Wavetable::kSine, {0}),
        Parameters(499, 100, 0, Wavetable::kSine, {0})
    };

    const LevelParameters Level11
            {
        Parameters(250, 100, 0.50, Wavetable::kSine, {0}),
        Parameters(750, 50, 0, Wavetable::kSine, {1}),
        Parameters(500, 100, 0, Wavetable::kSine, {0}),
        Parameters(250, 50, 0, Wavetable::kSine, {3})
            };

    const LevelParameters Level12
            {
        Parameters(1000, 100, 0, Wavetable::kSaw, {0}),
        Parameters(100, 100, 1.00, Wavetable::kCustom, {1})
            };

    const LevelParameters Level13
            {
        Parameters(750, 100, .50, Wavetable::kTriangle, {0}),
        Parameters(750, 100, 0, Wavetable::kSquare, {1}),
        Parameters(1500, 50, 0, Wavetable::kSine, {1})
            };

    const LevelParameters Level14
            {
        Parameters(900, 100, 0, Wavetable::kCustom, {0}),
        Parameters(600, 100, 0, Wavetable::kCustom, {1}),
        Parameters(3, 100, 0, Wavetable::kSine, {1, 2})
            };

    const LevelParameters Level15
    {
        Parameters(500, 100, 0, Wavetable::kSine, {0}),
        Parameters(100, 100, 0, Wavetable::kTriangle, {1})
    };
};


#endif //PATCH_MATCHER_LEVELGENERATOR_H
