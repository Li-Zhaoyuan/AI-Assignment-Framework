#include "Devil_AttackState.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Misc/GlobalFunctions.h"


Devil_AttackState::Devil_AttackState()
{
	Init(); 
}

Devil_AttackState::~Devil_AttackState()
{

}

void Devil_AttackState::Init()
{
	name_ = "DEVIL_ATTACK";
	changedName = false;

}

void Devil_AttackState::Update(double dt)
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
	
}

void Devil_AttackState::Exit()
{
	changedName = false;
	owner_of_component->setName(originalOwnerName);
}