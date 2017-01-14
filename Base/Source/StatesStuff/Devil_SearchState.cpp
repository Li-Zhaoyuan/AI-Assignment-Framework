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
	enemyLastSeen.SetZero();
	//chancesToActivate = 1;
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
	if (enemyLastSeen == Vector3(0, 0, 0))
	{

		if (timer >= 0.5f)
		{
			searchVel.x = Math::RandFloatMinMax(-50.f, 50.f);
			searchVel.y = Math::RandFloatMinMax(-50.f, 50.f);
			timer = 0;
		}
	}
	else
	{
		searchVel = (enemyLastSeen - zePhysicsStuff->getPos()).Normalized() * 40.f;
		
		if ((enemyLastSeen - zePhysicsStuff->getPos()).LengthSquared() < 100)
		{
			enemyLastSeen.SetZero();
		}
	}
	/*if ((zePhysicsStuff->getPos().x + zePhysicsStuff->getVel().x * dt) > zePhysicsStuff->getBoundary().x
		|| (zePhysicsStuff->getPos().x + zePhysicsStuff->getVel().x * dt) < -zePhysicsStuff->getBoundary().x)
		searchVel.x = -searchVel.x;
	if ((zePhysicsStuff->getPos().y + zePhysicsStuff->getVel().y * dt) > zePhysicsStuff->getBoundary().y
		|| (zePhysicsStuff->getPos().y + zePhysicsStuff->getVel().y * dt) < -zePhysicsStuff->getBoundary().y)
		searchVel.y = -searchVel.y;*/

	//zePhysicsStuff->getPos().x
	zePhysicsStuff->setVel(searchVel);
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

	AllyEnemyComponent *checkForEnemy = dynamic_cast<AllyEnemyComponent*>(&devil->getComponent(AllyEnemyComponent::ID_));
	for (std::vector<GameEntity*>::iterator it = checkForEnemy->m_enemyList->begin(), end = checkForEnemy->m_enemyList->end(); it != end; ++it)
	{
		PhysicsComponent *zeEnemyPhysics = dynamic_cast<PhysicsComponent*>(&(*it)->getComponent(PhysicsComponent::g_ID_));
		if ((zeEnemyPhysics->getPos() - zePhysicsStuff->getPos()).LengthSquared() <= 10000)
		{
			if (!checkWhetherTheWordInThatString("Bullet", (*it)->getName()))
			{
				zePhysicsStuff->setVel(Vector3(0, 0, 0));
				enemyLastSeen = zeEnemyPhysics->getPos();
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
	if (zeOwnselfHP->getHealth() <= 0)
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
    if (originalOwnerName != "")
        owner_of_component->setName(originalOwnerName);
}

bool Devil_SearchState::onNotify(const std::string &zeEvent)
{
	if (zeEvent.find("GO") != std::string::npos)    // Check to see if the event is for the guy to go. If so, extract the position out from the string
	{
		// The complex alogorithm to extract the position slowly
		std::string anotherStr = zeEvent.substr(3); // Hardcoding 3 because "GO:.....".thus extracting string after the ':'
		float x, y, z;
		size_t posOfComma = anotherStr.find(',');
		x = stof(anotherStr.substr(0, posOfComma));
		anotherStr = anotherStr.substr(posOfComma + 1);
		posOfComma = anotherStr.find(',');
		y = stof(anotherStr.substr(0, posOfComma));
		anotherStr = anotherStr.substr(posOfComma + 1);
		z = stof(anotherStr);

		enemyLastSeen.Set(x, y, z);
		return true;
	}
	return false;
}