#pragma once

#include "../Classes/GameEntity.h"
#include "../GenericECS/GenericComponent.h"

class CollisionComponent : public GenericComponent
{
public:
	CollisionComponent();
	virtual ~CollisionComponent();

	virtual void Init();
	virtual void Update(double dt);

	CollisionComponent &setEnemyList(std::vector<GameEntity*> &zeEnemy);
	CollisionComponent &setDespawnList(std::vector<GameEntity*> &zeDespawnList);
	//void setOwner(GameEntity* ownerOfbullet);

	static const unsigned char ID_ = 8;

	float influenceRange;
	std::vector<GameEntity*> *m_enemyList, *despawnList;
	//GameEntity* ownerOfbullet;
};