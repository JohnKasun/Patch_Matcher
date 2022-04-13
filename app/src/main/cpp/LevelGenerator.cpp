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
        default : return Level6;
    }
}
