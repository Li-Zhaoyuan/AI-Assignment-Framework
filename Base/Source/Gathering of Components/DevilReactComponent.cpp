#include "DevilReactComponent.h"
#include "../Classes/GameEntity.h"
#include "../StatesStuff/StateMachineComponent.h"
#include "AllyEnemyComponent.h"
#include "MyMath.h"

DevilReactComponent::DevilReactComponent()
{
	name_ = "Devil Reaction";
	receivedMessage = "";
	FSM_ = nullptr;
	chanceToReact = 1;
}

DevilReactComponent::~DevilReactComponent()
{

}

bool DevilReactComponent::onNotify(const std::string &zeEvent)
{
//msg in the format of MESSAGE|SENDER|RECIEVER|GO:
//only the DEVIL leader will have this COMPONENT
	if (zeEvent.find("Zombie") != std::string::npos
		&& zeEvent.find("Devil") != std::string::npos
		&& zeEvent.find("GO") != std::string::npos) // Check and see if this message is meant for the Devil, and wants the devil to go to a specific place.
	{
		if (!FSM_)// check if FSM_ is nullptr, if it is assign. initialise :V
		{
			GameEntity *zeOwner = dynamic_cast<GameEntity*>(owner_of_component);
			FSM_ = dynamic_cast<StateMachineComponent*>(&zeOwner->getComponent(StateMachineComponent::ID_.getValue()));
		}
		if (zeEvent.find("I DIED!") != std::string::npos)
		{
			GameEntity *zeOwner = dynamic_cast<GameEntity*>(owner_of_component);
			size_t posOfLastOr = zeEvent.find_last_of("|");
			std::string extractingTheMessage = zeEvent.substr(posOfLastOr + 1); // getting the position the entity have to go, which is where the zombie have died
			AllyEnemyComponent *checkOtherDevil = dynamic_cast<AllyEnemyComponent*>(&zeOwner->getComponent(AllyEnemyComponent::ID_));// the the ally list to find all the other devils
			for (std::vector<GameEntity*>::iterator it = checkOtherDevil->m_allyList->begin(), end = checkOtherDevil->m_allyList->end(); it != end; ++it) // iterate 
			{
				if ((*it)->getName().find("Devil") != std::string::npos)//find entities with Devil in the name that is not the  
				{
					GameEntity *zeOwner = dynamic_cast<GameEntity*>(*it);
					FSM_ = dynamic_cast<StateMachineComponent*>(&zeOwner->getComponent(StateMachineComponent::ID_.getValue()));
					int GettingTheChances = Math::RandIntMinMax(1, chanceToReact);  // get chance to make devil go to  the pos
					if (GettingTheChances == 1)
					{
						FSM_->switchState(0);
						FSM_->getCurrentState().onNotify(extractingTheMessage);
					}
				}
			}
			return true;
		}
	}
	return false;
}

bool DevilReactComponent::onNotify(const int &zeEvent)
{
	if (zeEvent > 0)
	{
		chanceToReact = zeEvent;
		return true;
	}
	return false;
}