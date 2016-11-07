#pragma once

#include "../Classes/GameEntity.h"

class NPCBuilder
{
public:
    static GameEntity *BuildZombie(const std::string &zeName);
    static GameEntity *BuildDog(const std::string &zeName);
};