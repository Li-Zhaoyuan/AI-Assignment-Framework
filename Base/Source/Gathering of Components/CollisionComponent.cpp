//CollisionComponent

#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include "HPandDPComponent.h"

CollisionComponent::CollisionComponent()
{
	Init();
}

CollisionComponent::~CollisionComponent()
{
	despawnList = nullptr;
	m_enemyList = nullptr;
}

void CollisionComponent::Init()
{
	despawnList = nullptr;
	m_enemyList = nullptr;
	influenceRange = 0;
}

void CollisionComponent::Update(double dt)
{
	GameEntity* ownself = dynamic_cast<GameEntity*>(owner_of_component);
	PhysicsComponent *zePhysics = dynamic_cast<PhysicsComponent*>(&(ownself)->getComponent(PhysicsComponent::g_ID_));
	HPandDPComponent *zeDamage = dynamic_cast<HPandDPComponent*>(&((ownself))->getComponent(HPandDPComponent::ID_));
	
	for (std::vector<GameEntity*>::iterator it = m_enemyList->begin(), end = m_enemyList->end(); it != end; ++it)
	{
		//GameEntity* ge = (*it);
		PhysicsComponent *zeEnemyPhysics = dynamic_cast<PhysicsComponent*>(&((*it))->getComponent(PhysicsComponent::g_ID_));
		HPandDPComponent *zeEnemyHP = dynamic_cast<HPandDPComponent*>(&((*it))->getComponent(HPandDPComponent::ID_));
		Vector3 dir = zeEnemyPhysics->getPos() - zePhysics->getPos();

		influenceRange = zeEnemyPhysics->getPos().x * zeEnemyPhysics->getPos().x;
		
		if (dir.LengthSquared() < 100)
		{
			despawnList->push_back(ownself);
			zeEnemyHP->getHealth() -= zeDamage->getDamage();
			break;
		}
		if (zePhysics->getPos().x > zePhysics->getBoundary().x
			|| zePhysics->getPos().x < -zePhysics->getBoundary().x
			|| zePhysics->getPos().y > zePhysics->getBoundary().y
			|| zePhysics->getPos().y < -zePhysics->getBoundary().y)
		{
			despawnList->push_back(ownself);
			break;
		}
	}
	/*if (zePhysics->getPos().x > zePhysics->getBoundary().x
		|| zePhysics->getPos().x < -zePhysics->getBoundary().x
		|| zePhysics->getPos().y > zePhysics->getBoundary().y
		|| zePhysics->getPos().y < -zePhysics->getBoundary().y)
	{
		despawnList->push_back(ownself);
	}*/
}

CollisionComponent &CollisionComponent::setDespawnList(std::vector<GameEntity*> &zeDespawnList)
{
	despawnList = &zeDespawnList;
	return *this;
}

CollisionComponent &CollisionComponent::setEnemyList(std::vector<GameEntity*> &zeEnemy)
{
	m_enemyList = &zeEnemy;
	return *this;
}