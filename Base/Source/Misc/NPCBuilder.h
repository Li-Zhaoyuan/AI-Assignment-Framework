#pragma once

#include "../Classes/GameEntity.h"
#include <vector>
#include "Vector3.h"
#include "DetectMemoryLeak.h"

class NPCBuilder
{
public:
    static GameEntity *BuildZombie(const std::string &zeName, Vector3 &boundary, std::vector<GameEntity*> &enemyList, std::vector<GameEntity*> &allyList, const Vector3 &zePos = Vector3(0,0,0));
    static GameEntity *BuildDog(const std::string &zeName, Vector3 &boundary, std::vector<GameEntity*> &enemyList, std::vector<GameEntity*> &allyList, const Vector3 &zePos = Vector3(0,0,0));
	static GameEntity *BuildDevil(const std::string &zeName, Vector3 &boundary, std::vector<GameEntity*> &enemyList, std::vector<GameEntity*> &allyList, const Vector3 &zePos = Vector3(0, 0, 0));
	static GameEntity *BuildGuy(const std::string &zeName, Vector3 &boundary, std::vector<GameEntity*> &enemyList, std::vector<GameEntity*> &allyList, const Vector3 &zePos = Vector3(0, 0, 0));
	static GameEntity *BuildBullet(const std::string &zeName, Vector3 &boundary, std::vector<GameEntity*> &enemyList, std::vector<GameEntity*> &allyList, std::vector<GameEntity*> &listtodespawn, const Vector3 &zePos = Vector3(0, 0, 0));
};