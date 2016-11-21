#include "Devil_HealState.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Misc/GlobalFunctions.h"
#include "../Gathering of Components/HPandDPComponent.h"

#define speed 40

Devil_HealState::Devil_HealState()
{
	Init();
}

Devil_HealState::~Devil_HealState()
{

}

void Devil_HealState::Init()
{
	name_ = " : HEAL";
	changedName = false;
	timer = 0;
	//influenceRadius = 10000;
}

void Devil_HealState::Update(double dt)
{
	
	switch (changedName)
	{
	case false:
	{
				  std::string newName = owner_of_component->getName();
				  originalOwnerName = newName;
				  newName.append(name_);
				  owner_of_component->setName(newName);
				  changedName = true;
	}
		break;
	default:
		break;
	}
	GameEntity* devil = dynamic_cast<GameEntity*>(owner_of_component);
	HPandDPComponent *zeHP = dynamic_cast<HPandDPComponent*>(&(devil)->getComponent(HPandDPComponent::ID_));
	PhysicsComponent *zePhysicsStuff = dynamic_cast<PhysicsComponent*>(&(devil)->getComponent(PhysicsComponent::g_ID_));
	AllyEnemyComponent *zeEnemy = dynamic_cast<AllyEnemyComponent*>(&(devil)->getComponent(AllyEnemyComponent::ID_));
	Vector3 dir;
	zePhysicsStuff->setVel(Vector3(0, 0, 0));
	for (std::vector<GameEntity*>::iterator it = zeEnemy->m_enemyList->begin(), end = zeEnemy->m_enemyList->end(); it != end; ++it)
	{
		PhysicsComponent *zeEnemyPhysics = dynamic_cast<PhysicsComponent*>(&(*it)->getComponent(PhysicsComponent::g_ID_));
		dir = (zeEnemyPhysics->getPos() - zePhysicsStuff->getPos());
		if (dir.LengthSquared() < 10000)
		{
			FSM_->switchState(2);
		}
	}
	timer += (float)dt;
	if (zeHP->getHealth() < 100 && timer > 0.5f)
	{
		zeHP->getHealth() += 5;
		if (zeHP->getHealth() > 100)
			zeHP->getHealth() = 100;
		timer = 0;
	}
	if (zeHP->getHealth() == 100)
	{
		FSM_->switchState(0);
	}

	if (zeHP->getHealth() < 0)
	{
		zePhysicsStuff->setVel(Vector3(0, 0, 0));
		zePhysicsStuff->setPos(Vector3(Math::RandFloatMinMax(-zePhysicsStuff->getBoundary().x, zePhysicsStuff->getBoundary().x), Math::RandFloatMinMax(-zePhysicsStuff->getBoundary().y, zePhysicsStuff->getBoundary().y), 0));
		zeHP->getHealth() = 100;

		FSM_->switchState(0);
	}
}

void Devil_HealState::Exit()
{
	changedName = false;
	owner_of_component->setName(originalOwnerName);
}