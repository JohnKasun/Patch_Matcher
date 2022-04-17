//
// Created by JohnK on 4/12/2022.
//

#include "LevelGenerator.h"

LevelGenerator::LevelGenerator() {

}

LevelGenerator::~LevelGenerator() {

}

LevelParameters LevelGenerator::getLevelParameters(int level) const {
    switch (level)
    {
        case 1 : return Level1;
        case 2 : return Level2;
        case 3 : return Level3;
        case 4 : return Level4;
        case 5 : return Level5;
        case 6 : return Level6;
        case 7 : return Level7;
        case 8 : return Level8;
        case 9 : return Level9;
        case 10 : return Level10;
        case 11 : return Level11;
        case 12 : return Level12;
        case 13 : return Level13;
        case 14 : return Level14;
        default : return Level15;
    }
}

LevelParameters LevelGenerator::getTutorialParameters() const {
    return Tutorial;
}
