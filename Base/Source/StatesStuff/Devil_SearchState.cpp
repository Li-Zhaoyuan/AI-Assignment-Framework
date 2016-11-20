#include "Devil_SearchState.h"
#include "..\Gathering of Components\PhysicsComponent.h"
#include "..\Classes\GameEntity.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../Gathering of Components/HPandDPComponent.h"
#include "../Misc/GlobalFunctions.h"

Devil_SearchState::Devil_SearchState()
{
	Init();
}

Devil_SearchState::~Devil_SearchState()
{

}

void Devil_SearchState::Init()
{
	name_ = " : SEARCH";
	changedName = false;
	timer = 0;
	searchVel.SetZero();
}

void Devil_SearchState::Update(double dt)
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

	//int randomDir = rand() % 4 + 1;
	timer += (float)dt;
	if (timer >= 0.5f)
	{
		searchVel.x = Math::RandFloatMinMax(-50.f, 50.f);
		searchVel.y = Math::RandFloatMinMax(-50.f, 50.f);
		timer = 0;
	}
	
	if ((zePhysicsStuff->getPos().x + zePhysicsStuff->getVel().x * dt) > zePhysicsStuff->getBoundary().x
		|| (zePhysicsStuff->getPos().x + zePhysicsStuff->getVel().x * dt) < -zePhysicsStuff->getBoundary().x)
		searchVel.x = -searchVel.x;
	if ((zePhysicsStuff->getPos().y + zePhysicsStuff->getVel().y * dt) > zePhysicsStuff->getBoundary().y
		|| (zePhysicsStuff->getPos().y + zePhysicsStuff->getVel().y * dt) < -zePhysicsStuff->getBoundary().y)
		searchVel.y = -searchVel.y;
	//zePhysicsStuff->getPos().x
	zePhysicsStuff->setVel(Vector3(searchVel.x, searchVel.y, 0));

	AllyEnemyComponent *checkForEnemy = dynamic_cast<AllyEnemyComponent*>(&devil->getComponent(AllyEnemyComponent::ID_));
	for (std::vector<GameEntity*>::iterator it = checkForEnemy->m_enemyList->begin(), end = checkForEnemy->m_enemyList->end(); it != end; ++it)
	{
		PhysicsComponent *zeEnemyPhysics = dynamic_cast<PhysicsComponent*>(&(*it)->getComponent(PhysicsComponent::g_ID_));
		if ((zeEnemyPhysics->getPos() - zePhysicsStuff->getPos()).LengthSquared() <= 10000)
		{
			if (checkWhetherTheWordInThatString("Guy", (*it)->getName()))
			{
				zePhysicsStuff->setVel(Vector3(0, 0, 0));
				FSM_->switchState(1);
			}

		}
	}
	HPandDPComponent *zeOwnselfHP = dynamic_cast<HPandDPComponent*>(&devil->getComponent(HPandDPComponent::ID_));
	
	if (zeOwnselfHP->getHealth() < 50)
	{
		zePhysicsStuff->setVel(Vector3(0, 0, 0));

		//currPoint = 0;
		FSM_->switchState(2);
	}
	if (zeOwnselfHP->getHealth() < 0)
	{
		zePhysicsStuff->setVel(Vector3(0, 0, 0));
		zePhysicsStuff->setPos(Vector3(Math::RandFloatMinMax(-zePhysicsStuff->getBoundary().x, zePhysicsStuff->getBoundary().x), Math::RandFloatMinMax(-zePhysicsStuff->getBoundary().y, zePhysicsStuff->getBoundary().y), 0));
		zeOwnselfHP->getHealth() = 100;

		FSM_->switchState(0);
	}
}

void Devil_SearchState::Exit()
{
	changedName = false;
	owner_of_component->setName(originalOwnerName);
}