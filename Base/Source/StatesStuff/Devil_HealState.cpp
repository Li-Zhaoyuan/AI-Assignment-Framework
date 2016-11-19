#include "Devil_HealState.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Misc/GlobalFunctions.h"
#include "../Gathering of Components/HPandDPComponent.h"

#define speed 40

Devil_HealState::Devil_HealState()
{
	Init();
}

Devil_HealState::~Devil_HealState()
{

}

void Devil_HealState::Init()
{
	name_ = " : HEAL";
	changedName = false;
	timer = 0;
}

void Devil_HealState::Update(double dt)
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
	HPandDPComponent *zeHP = dynamic_cast<HPandDPComponent*>(&(devil)->getComponent(HPandDPComponent::ID_));
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
}

void Devil_HealState::Exit()
{
	changedName = false;
	owner_of_component->setName(originalOwnerName);
}