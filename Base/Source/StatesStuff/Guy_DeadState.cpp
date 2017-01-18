#include "Guy_DeadState.h"
#include "..\Gathering of Components\PhysicsComponent.h"
#include "..\Classes\GameEntity.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../Gathering of Components/HPandDPComponent.h"
#include "../Misc/GlobalFunctions.h"

Guy_DeadState::Guy_DeadState()
{
	Init();
}

Guy_DeadState::~Guy_DeadState()
{

}

void Guy_DeadState::Init()
{
	name_ = " : DEAD";
	changedName = false;
}

void Guy_DeadState::Update(double dt)
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
	HPandDPComponent *zeOwnselfHP = dynamic_cast<HPandDPComponent*>(&guy->getComponent(HPandDPComponent::ID_));

    if (guy->seeComponentActive(11))    // Checking to see if it has the leader component, if so change the leader!
    {
        AllyEnemyComponent *listOfAllyEnemy = dynamic_cast<AllyEnemyComponent*>(&guy->getComponent(AllyEnemyComponent::ID_));
        for (std::vector<GameEntity*>::iterator it = listOfAllyEnemy->m_allyList->begin(), end = listOfAllyEnemy->m_allyList->end(); it != end; ++it)   // check through the ally list and see if there is any other guy, if so pass it to him
        {
            if ((*it)->getName().find("Guy") != std::string::npos && !(*it)->seeComponentActive(11))    // Check if it is the guy and see whether he does not have a leadership role. if so pass to him!
            {
                GenericComponent *zeLeaderComponent = guy->eraseComponent(11);
                (*it)->addComponent(11, zeLeaderComponent); // Give ze leadership position.
                break;
            }
        }
        // If can't find the guy, this entity shall keep the leadership position and dies with it
    }

	zePhysicsStuff->setVel(Vector3(0, 0, 0));//respawn reset
	zePhysicsStuff->setPos(Vector3(Math::RandFloatMinMax(-zePhysicsStuff->getBoundary().x, zePhysicsStuff->getBoundary().x), Math::RandFloatMinMax(-zePhysicsStuff->getBoundary().y, zePhysicsStuff->getBoundary().y), 0));
	zeOwnselfHP->getHealth() = 100;
	FSM_->switchState(0);
}

void Guy_DeadState::Exit()
{
	changedName = false;
	if (originalOwnerName != "")
		owner_of_component->setName(originalOwnerName);
}