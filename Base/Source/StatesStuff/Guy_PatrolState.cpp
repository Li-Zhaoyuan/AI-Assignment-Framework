#include "Guy_PatrolState.h"
#include "..\Gathering of Components\PhysicsComponent.h"
#include "..\Classes\GameEntity.h"
#include <math.h>
#define speed 30

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
	hasNameChange = false;
	rangeToStartPatrolling = 50;
	timer = 0;
	patrolAngle = 0;
	radiusToPatrolPoint = 50;
	searchVel.SetZero();
	pointToPatrol.SetZero();
	originToPatrolPos.SetZero();
}

void Guy_PatrolState::Update(double dt)
{
	switch (hasNameChange)
	{
	case false:
	{
				  std::string newName = owner_of_component->getName();
				  originalOwnerName = newName;
				  newName.append(name_);
				  owner_of_component->setName(newName);
				  hasNameChange = true;
	}
		break;
	default:
		break;
	}
	GameEntity* guy = dynamic_cast<GameEntity*>(owner_of_component);
	PhysicsComponent *zePhysicsStuff = dynamic_cast<PhysicsComponent*>(&(guy)->getComponent(PhysicsComponent::g_ID_));

	//int randomDir = rand() % 4 + 1;
	originToPatrolPos = (zePhysicsStuff->getPos() - pointToPatrol);
	radiusToPatrolPoint = (zePhysicsStuff->getPos() - pointToPatrol).Length();
	if (radiusToPatrolPoint <= 40 && radiusToPatrolPoint > 0)
	{
		patrolAngle = asinf(originToPatrolPos.y / radiusToPatrolPoint);
		searchVel = (zePhysicsStuff->getPos() - pointToPatrol).Normalized() * speed;
		zePhysicsStuff->setVel(Vector3(searchVel.x, searchVel.y, 0));
	}
	else if (radiusToPatrolPoint == 0)
	{
		patrolAngle = asinf(originToPatrolPos.y / radiusToPatrolPoint);
		Vector3 temp;
		temp.Set(5, 5, 0);
		searchVel = temp.Normalized() * speed;
		
		zePhysicsStuff->setVel(Vector3(searchVel.x , searchVel.y, 0));
	}
	else if (radiusToPatrolPoint <= rangeToStartPatrolling)
	{

		patrolAngle += dt;
		float fX, fY;
		fX = (pointToPatrol.x + cosf(patrolAngle) * radiusToPatrolPoint);
		fY = (pointToPatrol.y + sinf(patrolAngle) * radiusToPatrolPoint);
		zePhysicsStuff->setPos(Vector3(fX, fY, 0));
		rangeToStartPatrolling = 55;
		zePhysicsStuff->setVel(Vector3(0, 0, 0));
		
	}
	else
	{
		patrolAngle = asinf(originToPatrolPos.y / radiusToPatrolPoint);
		rangeToStartPatrolling = 50;
		searchVel = -(zePhysicsStuff->getPos() - pointToPatrol).Normalized() * speed;
		zePhysicsStuff->setVel(Vector3(searchVel.x, searchVel.y, 0));
		//radiusToPatrolPoint = (zePhysicsStuff->getPos() - pointToPatrol).Length();
	}
	
	

	
	//zePhysicsStuff->getPos().x
	//zePhysicsStuff->setVel(Vector3(searchVel.x, searchVel.y, 0));


}

void Guy_PatrolState::Exit()
{
	changedName = false;
	owner_of_component->setName(originalOwnerName);
}