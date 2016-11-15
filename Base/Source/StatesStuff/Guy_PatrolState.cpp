#include "Guy_PatrolState.h"
#include "..\Gathering of Components\PhysicsComponent.h"
#include "..\Classes\GameEntity.h"
#include "../Gathering of Components/HPandDPComponent.h"

#include <math.h>
#define speed 50
#define healthProcValue 50
#define rangeToPatrolPoint 100

Guy_PatrolState::Guy_PatrolState()
{
	Init();
}

Guy_PatrolState::~Guy_PatrolState()
{

}

void Guy_PatrolState::Init()
{
	name_ = " : PATROL";
	
	changedName = false;
	isAtWayPoint = false;
	pointToPatrol.SetZero(); 
	vel.SetZero();
	currPoint = 0;
	nextPoint = 0;
	setWayPoints();
}

void Guy_PatrolState::Update(double dt)
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
	
	if (hpOfGuy->getHealth() < healthProcValue)
	{
		zePhysicsStuff->setVel(Vector3(0, 0, 0));
		isAtWayPoint = false;
		//currPoint = 0;
		FSM_->switchState(1);
	}
	if (isAtWayPoint == false)
	{
		if ((zePhysicsStuff->getPos() - wayPoints[currPoint]).LengthSquared() <= 10)
		{
			isAtWayPoint = true;
		}
		else
		{
			Vector3 temp;
			temp = -(zePhysicsStuff->getPos() - wayPoints[currPoint]);
			temp.Normalize();
			temp *= speed;
			vel.Set(temp.x, temp.y, temp.z);
		}
	}
	if (isAtWayPoint == true)
	{
		nextPoint = currPoint + 1;
		if (nextPoint == 4)
		{
			nextPoint = 0;
		}
		if ((zePhysicsStuff->getPos() - wayPoints[nextPoint]).LengthSquared() <= 10)
		{
			currPoint += 1;
			if (currPoint == 4)
			{
				currPoint = 0;
			}
		}
		else
		{
			Vector3 temp;
			temp = -(zePhysicsStuff->getPos() - wayPoints[nextPoint]);
			temp.Normalize();
			temp *= speed;
			vel.Set(temp.x, temp.y, temp.z);
		}
	}
	
	zePhysicsStuff->setVel(vel);
	//zePhysicsStuff->getPos().x
	//zePhysicsStuff->setVel(Vector3(searchVel.x, searchVel.y, 0));


}

void Guy_PatrolState::Exit()
{
	changedName = false;
	owner_of_component->setName(originalOwnerName);
}

void Guy_PatrolState::setWayPoints()
{
	wayPoints[0].Set(pointToPatrol.x, pointToPatrol.y + rangeToPatrolPoint, 0);
	wayPoints[1].Set(pointToPatrol.x, pointToPatrol.y - rangeToPatrolPoint, 0);
	wayPoints[2].Set(pointToPatrol.x + rangeToPatrolPoint, pointToPatrol.y, 0);
	wayPoints[3].Set(pointToPatrol.x - rangeToPatrolPoint, pointToPatrol.y, 0);
}