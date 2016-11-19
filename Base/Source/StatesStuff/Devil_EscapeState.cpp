#include "Devil_EscapeState.h"
#include "..\Gathering of Components\PhysicsComponent.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "..\Classes\GameEntity.h"
#include "../Misc/GlobalFunctions.h"
#include "../Gathering of Components/HPandDPComponent.h"
#include <math.h>
#define speed 60

Devil_EscapeState::Devil_EscapeState()
{
	Init();
}

Devil_EscapeState::~Devil_EscapeState()
{

}

void Devil_EscapeState::Init()
{
	name_ = " : ESCAPE";

	timer = 0;
	changedName = false;
}

void Devil_EscapeState::Update(double dt)

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
	timer += (float)dt;
	GameEntity* devil = dynamic_cast<GameEntity*>(owner_of_component);
	PhysicsComponent *zePhysicsStuff = dynamic_cast<PhysicsComponent*>(&(devil)->getComponent(PhysicsComponent::g_ID_));

	//int randomDir = rand() % 4 + 1;
	Vector3 temp;
	AllyEnemyComponent *checkForEnemy = dynamic_cast<AllyEnemyComponent*>(&devil->getComponent(AllyEnemyComponent::ID_));
	for (std::vector<GameEntity*>::iterator it = checkForEnemy->m_enemyList->begin(), end = checkForEnemy->m_enemyList->end(); it != end; ++it)
	{
		PhysicsComponent *zeEnemyPhysics = dynamic_cast<PhysicsComponent*>(&(*it)->getComponent(PhysicsComponent::g_ID_));
		if ((zeEnemyPhysics->getPos() - zePhysicsStuff->getPos()).LengthSquared() <= 1000)
		{
			if (checkWhetherTheWordInThatString("Guy", (*it)->getName()))
			{
				temp = -(zeEnemyPhysics->getPos() - zePhysicsStuff->getPos()).Normalized() * speed;
				zePhysicsStuff->setVel(temp);
				//FSM_->switchState(1);
			}

		}
		else
		{
			FSM_->switchState(3);
		}
	}

	//if (zePhysicsStuff->getPos())

	//zePhysicsStuff->getPos().x
	//zePhysicsStuff->setVel(Vector3(searchVel.x, searchVel.y, 0));
	HPandDPComponent *zeHP = dynamic_cast<HPandDPComponent*>(&(devil)->getComponent(HPandDPComponent::ID_));
	if (zePhysicsStuff->getPos().x > zePhysicsStuff->getBoundary().x)
	{
		zePhysicsStuff->getPos().x -= zePhysicsStuff->getBoundary().x * 2;
	}
	else if (zePhysicsStuff->getPos().x < -zePhysicsStuff->getBoundary().x)
	{
		zePhysicsStuff->getPos().x += zePhysicsStuff->getBoundary().x * 2;
	}

	if (zePhysicsStuff->getPos().y > zePhysicsStuff->getBoundary().y)
	{
		zePhysicsStuff->getPos().y -= zePhysicsStuff->getBoundary().y * 2;
	}
	else if (zePhysicsStuff->getPos().y < -zePhysicsStuff->getBoundary().y)
	{
		zePhysicsStuff->getPos().y += zePhysicsStuff->getBoundary().y * 2;
	}

	/*if (zeHP->getHealth() < 100 && timer > 0.5f)
	{
		zeHP->getHealth() += 2;
		timer = 0;
	}
	else if (zeHP->getHealth() == 100)
	{
		FSM_->switchState(0);
	}*/

}

void Devil_EscapeState::Exit()
{
	changedName = false;
	owner_of_component->setName(originalOwnerName);
}