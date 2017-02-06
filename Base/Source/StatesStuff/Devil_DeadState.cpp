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
	
	if (devil->seeComponentActive(11))//make sure is ldr
	{
		AllyEnemyComponent *listofAlly = dynamic_cast<AllyEnemyComponent*>(&devil->getComponent(AllyEnemyComponent::ID_));
		for (std::vector<GameEntity*>::iterator it = listofAlly->m_allyList->begin(), end = listofAlly->m_allyList->end(); it != end; ++it)   // check through the ally list and see if there is any other Devil, if so pass it to him
		{
			if ((*it)->getName().find("Devil") != std::string::npos && !(*it)->seeComponentActive(11))    // Check if it is the devil and see whether he does not have a leadership role. if so pass to him!
			{
				GenericComponent *zeLeaderComponent = devil->eraseComponent(11);
				(*it)->addComponent(11, zeLeaderComponent); // Give ze leadership position.
				break;
			}
		}
	}

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