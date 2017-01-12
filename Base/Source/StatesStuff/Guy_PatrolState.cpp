#include "Guy_PatrolState.h"
#include "..\Gathering of Components\PhysicsComponent.h"
#include "..\Classes\GameEntity.h"
#include "../Gathering of Components/HPandDPComponent.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../Misc/GlobalFunctions.h"
#include <math.h>
#define speed 50
#define healthProcValue 50
#define rangeToPatrolPoint Math::RandFloatMinMax(50,150)

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
	originalOwnerName = "";
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
	AllyEnemyComponent *checkForEnemy = dynamic_cast<AllyEnemyComponent*>(&guy->getComponent(AllyEnemyComponent::ID_));
	for (std::vector<GameEntity*>::iterator it = checkForEnemy->m_enemyList->begin(), end = checkForEnemy->m_enemyList->end(); it != end; ++it)
	{
		PhysicsComponent *zeEnemyPhysics = dynamic_cast<PhysicsComponent*>(&(*it)->getComponent(PhysicsComponent::g_ID_));
		if ((zeEnemyPhysics->getPos() - zePhysicsStuff->getPos()).LengthSquared() <= 10000)
		{
			//if (checkWhetherTheWordInThatString("Devil", (*it)->getName()))
			{
				zePhysicsStuff->setVel(Vector3(0, 0, 0));
				FSM_->switchState(3);
			}

		}
	}
	//zePhysicsStuff->getPos().x
	//zePhysicsStuff->setVel(Vector3(searchVel.x, searchVel.y, 0));
	
	if (hpOfGuy->getHealth() <= 0)
	{

		zePhysicsStuff->setVel(Vector3(0, 0, 0));
		zePhysicsStuff->setPos(Vector3(Math::RandFloatMinMax(-zePhysicsStuff->getBoundary().x, zePhysicsStuff->getBoundary().x), Math::RandFloatMinMax(-zePhysicsStuff->getBoundary().y, zePhysicsStuff->getBoundary().y), 0));
		hpOfGuy->getHealth() = 100;
		/*changedName = false;
		isAtWayPoint = false;
		pointToPatrol.SetZero();
		vel.SetZero();
		currPoint = 0;
		nextPoint = 0;
		setWayPoints();*/
		FSM_->switchState(0);
	}
	//setWayPoints();
}

void Guy_PatrolState::Exit()
{
	changedName = false;
    if (originalOwnerName != "")
        owner_of_component->setName(originalOwnerName);
}

void Guy_PatrolState::setWayPoints()
{
	wayPoints[0].Set(pointToPatrol.x, pointToPatrol.y + rangeToPatrolPoint, 0);
	wayPoints[1].Set(pointToPatrol.x, pointToPatrol.y - rangeToPatrolPoint, 0);
	wayPoints[2].Set(pointToPatrol.x + rangeToPatrolPoint, pointToPatrol.y, 0);
	wayPoints[3].Set(pointToPatrol.x - rangeToPatrolPoint, pointToPatrol.y, 0);
}

bool Guy_PatrolState::onNotify(const std::string &zeEvent)
{
    if (zeEvent.find("GO") != std::string::npos)    // Check to see if the event is for the guy to go. If so, extract the position out from the string
    {
        currPoint = 0;
        nextPoint = 0;

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

        wayPoints[0].Set(x, y, z);
        wayPoints[3] = wayPoints[2] = wayPoints[1] = wayPoints[0];  // Need to make sure all the waypoints are in the same position otherwise the Guy will just go haywire!

        return true;
    }
    return false;
}