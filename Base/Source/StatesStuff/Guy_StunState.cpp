#include "Guy_StunState.h"
#include "..\Gathering of Components\PhysicsComponent.h"
#include "..\Classes\GameEntity.h"
#include "../Gathering of Components/HPandDPComponent.h"

#include <math.h>
#define speed 50
#define healthProcValue 50
#define rangeToPatrolPoint 100

Guy_StunState::Guy_StunState()
{
	Init();
}

Guy_StunState::~Guy_StunState()
{

}

void Guy_StunState::Init()
{
	name_ = " : STUNNED";

	changedName = false;
	timer = 0;
}

void Guy_StunState::Update(double dt)
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

	timer += dt;

	zePhysicsStuff->getVel().SetZero();

	if (timer > 3)
	{
		FSM_->switchState(0);
		timer = 0;
	}

}

void Guy_StunState::Exit()
{
	changedName = false;
	owner_of_component->setName(originalOwnerName);
	timer = 0;
}
