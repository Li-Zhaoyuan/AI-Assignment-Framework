#include "Devil_AttackState.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Misc/GlobalFunctions.h"
#include "../Gathering of Components/HPandDPComponent.h"
#include "../StatesStuff/StateMachineComponent.h"

#define speed 60

Devil_AttackState::Devil_AttackState()
{
	Init(); 
}

Devil_AttackState::~Devil_AttackState()
{

}

void Devil_AttackState::Init()
{
	name_ = " : ATTACK";
	changedName = false;
	timer = 0;
	chance = 0;
}

void Devil_AttackState::Update(double dt)
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
	PhysicsComponent *zePhysicsStuff = dynamic_cast<PhysicsComponent*>(&(devil)->getComponent(PhysicsComponent::g_ID_));
	HPandDPComponent *zeOwnselfDP = dynamic_cast<HPandDPComponent*>(&(devil)->getComponent(HPandDPComponent::ID_));
	zePhysicsStuff->setVel(Vector3(0, 0, 0));

	timer += (float)dt;
	Vector3 dir;
	float closest = 20000;
	GameEntity* closestTarget;
	AllyEnemyComponent *checkForEnemy = dynamic_cast<AllyEnemyComponent*>(&devil->getComponent(AllyEnemyComponent::ID_));
	for (std::vector<GameEntity*>::iterator it = checkForEnemy->m_enemyList->begin(), end = checkForEnemy->m_enemyList->end(); it != end; ++it)
	{
		PhysicsComponent *zeEnemyPhysics = dynamic_cast<PhysicsComponent*>(&(*it)->getComponent(PhysicsComponent::g_ID_));
		dir = (zeEnemyPhysics->getPos() - zePhysicsStuff->getPos());
		if (dir.LengthSquared() <= closest && !checkWhetherTheWordInThatString("Bullet", (*it)->getName()))
		{
			//if (checkWhetherTheWordInThatString("Guy", (*it)->getName()))
			{
				closest = dir.LengthSquared();
				closestTarget = (*it);
				

			}
		}
	}

	if (closest == 20000)
	{
		zePhysicsStuff->setVel(Vector3(0, 0, 0));
		FSM_->switchState(0);
	}
	else
	{
		Vector3 temp;
		PhysicsComponent *zeEnemyPhysics = dynamic_cast<PhysicsComponent*>(&(closestTarget)->getComponent(PhysicsComponent::g_ID_));
		HPandDPComponent *zeEnemyHP = dynamic_cast<HPandDPComponent*>(&(closestTarget)->getComponent(HPandDPComponent::ID_));
		StateMachineComponent *zeEnemyCurrState = dynamic_cast<StateMachineComponent*>(&(closestTarget)->getComponent(StateMachineComponent::ID_.getValue()));
		temp = (zeEnemyPhysics->getPos() - zePhysicsStuff->getPos()).Normalized() * speed;
		zePhysicsStuff->setVel(temp);
		if ((zeEnemyPhysics->getPos() - zePhysicsStuff->getPos()).LengthSquared() <= 1000 && timer > 2)
		{
			zeEnemyHP->getHealth() -= zeOwnselfDP->getDamage();
			//zePhysicsStuff->setVel(Vector3(0, 0, 0));
			chance = Math::RandIntMinMax(1, 4);
			if (chance > 2)
			{
				if (zeEnemyCurrState->getCurrentState().getName() != zeEnemyCurrState->getSpecificStates(2).getName() && checkWhetherTheWordInThatString("Guy", (closestTarget)->getName()))
					zeEnemyCurrState->switchState(2);
				chance = 0;
			}
			//zeEnemyCurrState->switchState(2);
			timer = 0;
		}
		if ((zeEnemyPhysics->getPos() - zePhysicsStuff->getPos()).LengthSquared() <= 1000)
		{
			zePhysicsStuff->setVel(Vector3(0, 0, 0));
		}
	}

	if (zeOwnselfDP->getHealth() < 50)
	{
		zePhysicsStuff->setVel(Vector3(0, 0, 0));
		
		//currPoint = 0;
		FSM_->switchState(2);
	}
	//zeOwnselfDP->getHealth() = 100;
	if (zeOwnselfDP->getHealth() <= 0)
	{
		FSM_->switchState(4);
	}
}

void Devil_AttackState::Exit()
{
	changedName = false;
    if (originalOwnerName != "")
	    owner_of_component->setName(originalOwnerName);
}