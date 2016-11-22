#include "Guy_AttackState.h"
#include "..\Gathering of Components\PhysicsComponent.h"
#include "..\Classes\GameEntity.h"
#include <sstream>
#include "../Gathering of Components/HPandDPComponent.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "..\\Systems\\Scene_System.h"

#include <math.h>
#define speed 35
#define healthProcValue 50
#define rangeToPatrolPoint 100

Guy_AttackState::Guy_AttackState()
{
	Init();
}

Guy_AttackState::~Guy_AttackState()
{

}

void Guy_AttackState::Init()
{
	name_ = " : ATTACK";
	originalOwnerName = "";
	changedName = false;
	timer = 2.f;
}

void Guy_AttackState::Update(double dt)
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
	GameEntity* guy = dynamic_cast<GameEntity*>(owner_of_component);
	PhysicsComponent *zePhysicsStuff = dynamic_cast<PhysicsComponent*>(&(guy)->getComponent(PhysicsComponent::g_ID_));
	HPandDPComponent* hpOfGuy = dynamic_cast<HPandDPComponent*>(&(guy)->getComponent(HPandDPComponent::ID_));
	AllyEnemyComponent* checkForEnemy = dynamic_cast<AllyEnemyComponent*>(&(guy)->getComponent(AllyEnemyComponent::ID_));

	timer += (float)dt;

	Vector3 dir;
	float closest = 10000;
	GameEntity* closestTarget;
	for (std::vector<GameEntity*>::iterator it = checkForEnemy->m_enemyList->begin(), end = checkForEnemy->m_enemyList->end(); it != end; ++it)
	{
		PhysicsComponent *zeEnemyPhysics = dynamic_cast<PhysicsComponent*>(&(*it)->getComponent(PhysicsComponent::g_ID_));
		dir = (zeEnemyPhysics->getPos() - zePhysicsStuff->getPos());
		
		if (dir.LengthSquared() < closest)
		{
			closest = dir.LengthSquared();
			closestTarget = (*it);
		}
	}
	if (closest == 10000)
	{
		FSM_->switchState(0);
	}
	else
	{
		Vector3 bulletVel;
		PhysicsComponent *closestTargetPhy = dynamic_cast<PhysicsComponent*>(&(closestTarget)->getComponent(PhysicsComponent::g_ID_));
		bulletVel = (closestTargetPhy->getPos() - zePhysicsStuff->getPos()).Normalized() * (speed * 2);
		if ((closestTargetPhy->getPos() - zePhysicsStuff->getPos()).LengthSquared() < 5000)
		{
			Vector3 tempVel;
			tempVel = -(closestTargetPhy->getPos() - zePhysicsStuff->getPos()).Normalized() * speed;
			
			zePhysicsStuff->setVel(tempVel);
		}
		else
		{
			zePhysicsStuff->setVel(Vector3(0, 0, 0));
		}

		std::ostringstream ss;
		//ally/GO:X,Y,Z/POS:X,Y,Z 
		ss.str("");
		ss << "ally/GO:" << bulletVel.x << "," << bulletVel.y << "," << bulletVel.z << "/POS:" << zePhysicsStuff->getPos().x << "," << zePhysicsStuff->getPos().y << "," << zePhysicsStuff->getPos().z;

		if (timer > 2.f)
		{

			Scene_System::accessing().getCurrScene().onNotify(ss.str());
			timer = 0;
		}
		HPandDPComponent* hpOfGuy = dynamic_cast<HPandDPComponent*>(&(guy)->getComponent(HPandDPComponent::ID_));

		if (hpOfGuy->getHealth() < healthProcValue)
		{
			zePhysicsStuff->setVel(Vector3(0, 0, 0));
			
			//currPoint = 0;
			FSM_->switchState(1);
		}
	}
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
	//dir = (zePhysicsStuff->getPos());

	/*zePhysicsStuff->getVel().SetZero();

	if (timer > 3)
	{
		FSM_->switchState(0);
		timer = 0;
	}*/

	if (hpOfGuy->getHealth() <= 0)
	{

		zePhysicsStuff->setVel(Vector3(0, 0, 0));
		zePhysicsStuff->setPos(Vector3(Math::RandFloatMinMax(-zePhysicsStuff->getBoundary().x, zePhysicsStuff->getBoundary().x), Math::RandFloatMinMax(-zePhysicsStuff->getBoundary().y, zePhysicsStuff->getBoundary().y), 0));
		hpOfGuy->getHealth() = 100;

		FSM_->switchState(0);
	}
}

void Guy_AttackState::Exit()
{
	changedName = false;
    if (originalOwnerName != "")
        owner_of_component->setName(originalOwnerName);
    //timer = 2.f;
}
