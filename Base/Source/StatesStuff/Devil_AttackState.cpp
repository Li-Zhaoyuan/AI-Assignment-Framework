#include "Devil_AttackState.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Misc/GlobalFunctions.h"
#include "../Gathering of Components/HPandDPComponent.h"
#include "../StatesStuff/StateMachineComponent.h"

#define speed 40

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
	AllyEnemyComponent *checkForEnemy = dynamic_cast<AllyEnemyComponent*>(&devil->getComponent(AllyEnemyComponent::ID_));
	for (std::vector<GameEntity*>::iterator it = checkForEnemy->m_enemyList->begin(), end = checkForEnemy->m_enemyList->end(); it != end; ++it)
	{
		PhysicsComponent *zeEnemyPhysics = dynamic_cast<PhysicsComponent*>(&(*it)->getComponent(PhysicsComponent::g_ID_));
		HPandDPComponent *zeEnemyHP = dynamic_cast<HPandDPComponent*>(&(*it)->getComponent(HPandDPComponent::ID_));
		StateMachineComponent *zeEnemyCurrState = dynamic_cast<StateMachineComponent*>(&(*it)->getComponent(StateMachineComponent::ID_.getValue()));
		if ((zeEnemyPhysics->getPos() - zePhysicsStuff->getPos()).LengthSquared() <= 10000)
		{
			if (checkWhetherTheWordInThatString("Guy", (*it)->getName()))
			{
				Vector3 temp;
				temp = (zeEnemyPhysics->getPos() - zePhysicsStuff->getPos()).Normalized() * speed;
				zePhysicsStuff->setVel(temp);
				if ((zeEnemyPhysics->getPos() - zePhysicsStuff->getPos()).LengthSquared() <= 1000 && timer > 2)
				{
					zeEnemyHP->getHealth() -= zeOwnselfDP->getDamage();
					chance = Math::RandIntMinMax(1, 4);
					if (chance == 1)
					{
						zeEnemyCurrState->switchState(2);
						chance = 0;
					}
					//zeEnemyCurrState->switchState(2);
					timer = 0;
				}
			}
			break;
		}
		else
		{
			zePhysicsStuff->setVel(Vector3(0, 0, 0));
			FSM_->switchState(0);
		}
	}

	
}

void Devil_AttackState::Exit()
{
	changedName = false;
	owner_of_component->setName(originalOwnerName);
}