#include "Devil_DeadState.h"
#include "..\Gathering of Components\PhysicsComponent.h"
#include "..\Classes\GameEntity.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../Gathering of Components/HPandDPComponent.h"
#include "../Misc/GlobalFunctions.h"

Devil_DeadState::Devil_DeadState()
{
	Init();
}

Devil_DeadState::~Devil_DeadState()
{

}

void Devil_DeadState::Init()
{
	name_ = " : DEAD";
	changedName = false;
	//chancesToActivate = 1;
}

void Devil_DeadState::Update(double dt)
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
	HPandDPComponent *zeOwnselfHP = dynamic_cast<HPandDPComponent*>(&devil->getComponent(HPandDPComponent::ID_));
	
	zePhysicsStuff->setVel(Vector3(0, 0, 0));//respawn reset
	zePhysicsStuff->setPos(Vector3(Math::RandFloatMinMax(-zePhysicsStuff->getBoundary().x, zePhysicsStuff->getBoundary().x), Math::RandFloatMinMax(-zePhysicsStuff->getBoundary().y, zePhysicsStuff->getBoundary().y), 0));
	zeOwnselfHP->getHealth() = 100;
	FSM_->switchState(0);
}

void Devil_DeadState::Exit()
{
	changedName = false;
	if (originalOwnerName != "")
		owner_of_component->setName(originalOwnerName);
}