#pragma once

#include "../Classes/GameEntity.h"
#include <vector>
#include "Vector3.h"
#include "DetectMemoryLeak.h"

class NPCBuilder
{
public:
    static GameEntity *BuildZombie(const std::string &zeName, const Vector3 &boundary, std::vector<GameEntity*> &goList);
    static GameEntity *BuildDog(const std::string &zeName, const Vector3 &boundary, std::vector<GameEntity*> &goList);
};