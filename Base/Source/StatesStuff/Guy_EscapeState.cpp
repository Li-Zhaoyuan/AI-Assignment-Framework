#include "Guy_EscapeState.h"
#include "..\Gathering of Components\PhysicsComponent.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "..\Classes\GameEntity.h"
#include "../Misc/GlobalFunctions.h"
#include "../Gathering of Components/HPandDPComponent.h"
#include <math.h>
#include "../Systems/MessageSystem.h"
#include <sstream>
#define speed 60

Guy_EscapeState::Guy_EscapeState()
{
	Init();
}

Guy_EscapeState::~Guy_EscapeState()
{

}

void Guy_EscapeState::Init()
{
	name_ = " : ESCAPE";
	originalOwnerName = "";
	timer = 0;
	changedName = false;
}

void Guy_EscapeState::Update(double dt)
{
    // Shifting ur physics component up because i need to use it for sending coordinate to other entities
    GameEntity* guy = dynamic_cast<GameEntity*>(owner_of_component);
    PhysicsComponent *zePhysicsStuff = dynamic_cast<PhysicsComponent*>(&(guy)->getComponent(PhysicsComponent::g_ID_));
    switch (changedName)
	{
	case false:
	{
				  std::string newName = owner_of_component->getName();
				  originalOwnerName = newName;
				  newName.append(name_);
				  owner_of_component->setName(newName);
				  changedName = true;
                  // Putting the sending of message here because this state is activated when the guy's health is low.  This changedName will only happens once thus sending the message to the message system once!
                  std::ostringstream ss;
                  ss << "I am being attacked!|Guy|Dog|GO:" << zePhysicsStuff->getPos().x << "," << zePhysicsStuff->getPos().y << "," << zePhysicsStuff->getPos().z;
                  MessageSystem::accessing().onNotify(ss.str());
	}
		break;
	default:
		break;
	}
	timer += (float)dt;

	//int randomDir = rand() % 4 + 1;
	Vector3 temp;
	AllyEnemyComponent *checkForEnemy = dynamic_cast<AllyEnemyComponent*>(&guy->getComponent(AllyEnemyComponent::ID_));
	for (std::vector<GameEntity*>::iterator it = checkForEnemy->m_enemyList->begin(), end = checkForEnemy->m_enemyList->end(); it != end; ++it)
	{
		PhysicsComponent *zeEnemyPhysics = dynamic_cast<PhysicsComponent*>(&(*it)->getComponent(PhysicsComponent::g_ID_));
		if ((zeEnemyPhysics->getPos() - zePhysicsStuff->getPos()).LengthSquared() <= 10000)
		{
			//if (checkWhetherTheWordInThatString("Devil", (*it)->getName()))
			{
				temp = -(zeEnemyPhysics->getPos() - zePhysicsStuff->getPos()).Normalized() * speed;
				zePhysicsStuff->setVel(temp);
				//FSM_->switchState(1);
			}

		}
		if ((zeEnemyPhysics->getPos() - zePhysicsStuff->getPos()).LengthSquared() >= 10000)
		{
			//FSM_->switchState(2);
		}
	}

	//if (zePhysicsStuff->getPos())

	//zePhysicsStuff->getPos().x
	//zePhysicsStuff->setVel(Vector3(searchVel.x, searchVel.y, 0));
	HPandDPComponent *zeHP = dynamic_cast<HPandDPComponent*>(&(guy)->getComponent(HPandDPComponent::ID_));
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

	if (zeHP->getHealth() < 100 && timer > 0.5f)
	{
		zeHP->getHealth() += 2;
		if (zeHP->getHealth() > 100)
			zeHP->getHealth() = 100;
		timer = 0;
	}
	else if (zeHP->getHealth() == 100)
	{
		FSM_->switchState(0);
	}

	if (zeHP->getHealth() <= 0)
	{

		zePhysicsStuff->setVel(Vector3(0, 0, 0));
		zePhysicsStuff->setPos(Vector3(Math::RandFloatMinMax(-zePhysicsStuff->getBoundary().x, zePhysicsStuff->getBoundary().x), Math::RandFloatMinMax(-zePhysicsStuff->getBoundary().y, zePhysicsStuff->getBoundary().y), 0));
		zeHP->getHealth() = 100;

		FSM_->switchState(0);
	}
}

void Guy_EscapeState::Exit()
{
	changedName = false;
    if (originalOwnerName != "")
        owner_of_component->setName(originalOwnerName);
}