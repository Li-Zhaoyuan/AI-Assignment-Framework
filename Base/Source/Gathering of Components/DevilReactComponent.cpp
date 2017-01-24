#include "DevilReactComponent.h"
#include "../Classes/GameEntity.h"
#include "../StatesStuff/StateMachineComponent.h"
#include "AllyEnemyComponent.h"
#include "LeaderComponent.h"
#include "MyMath.h"

DevilReactComponent::DevilReactComponent()
{
	name_ = "Devil Reaction";
	receivedMessage = "";
	FSM_ = nullptr;
	chanceToReact = 2;
	HasReactToMessage = false;
}

DevilReactComponent::~DevilReactComponent()
{

}

bool DevilReactComponent::onNotify(const std::string &zeEvent)
{
//msg in the format of MESSAGE|SENDER|RECIEVER|GO:
	GameEntity *zeOwnerMain = dynamic_cast<GameEntity*>(owner_of_component);
	LeaderComponent *leader = dynamic_cast<LeaderComponent*>(&zeOwnerMain->getComponent(LeaderComponent::ID_));
	if ((zeOwnerMain)->seeComponentActive((LeaderComponent::ID_)))// make sure only the leader can make the decision
	{
		if (zeEvent.find("Zombie") != std::string::npos
			&& zeEvent.find("Devil<LDR>") != std::string::npos
			&& (zeEvent.find("Zombie") < zeEvent.find("Devil<LDR>"))// making sure the msg is the correct sender and meant for the correct person
			&& zeEvent.find("GO") != std::string::npos // Check and see if this message is meant for the Devil, and wants the devil to go to a specific place.
			&& !HasReactToMessage)//must befree to react to message
		{
			//if (!FSM_)// check if FSM_ is nullptr, if it is assign. initialise :V
			//{
			//	GameEntity *zeOwner = dynamic_cast<GameEntity*>(owner_of_component);
			//	FSM_ = dynamic_cast<StateMachineComponent*>(&zeOwner->getComponent(StateMachineComponent::ID_.getValue()));
			//}
			if (zeEvent.find("I DIED!") != std::string::npos)
			{

				size_t posOfLastOr = zeEvent.find_last_of("|");
				std::string extractingTheMessage = zeEvent.substr(posOfLastOr + 1); // getting the position the entity have to go, which is where the zombie have died
				AllyEnemyComponent *checkOtherDevil = dynamic_cast<AllyEnemyComponent*>(&zeOwnerMain->getComponent(AllyEnemyComponent::ID_));// the the ally list to find all the other devils
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
							FSM_->getCurrentState().onNotify(extractingTheMessage);//Reply
							FSM_->getCurrentState().onNotify("[Reply]");
						}
					}
				}
				return true;
			}
		}
		//else if (zeEvent.find("|Devil|") != std::string::npos//from
		//	&& zeEvent.find("Devil<LDR>") != std::string::npos//reciever
		//	&& (zeEvent.find("|Devil|") < zeEvent.find("Devil<LDR>")) // making sure the msg is the correct sender and meant for the correct person
		//	&& zeEvent.find("name") != std::string::npos)
		else if (zeEvent.find("Devil|Zombie&Devil<LDR>") != std::string::npos
			&& zeEvent.find("name") != std::string::npos)
		{
			if (zeEvent.find("I Need Assistance!") != std::string::npos)
			{
				
				AllyEnemyComponent *checkOtherDevil = dynamic_cast<AllyEnemyComponent*>(&zeOwnerMain->getComponent(AllyEnemyComponent::ID_));// the the ally list to find all the other devils
				for (std::vector<GameEntity*>::iterator it = checkOtherDevil->m_allyList->begin(), end = checkOtherDevil->m_allyList->end(); it != end; ++it) // iterate 
				{
					if ((*it)->getName().find("Devil") != std::string::npos)//find entities with Devil in the name that is not the  
					{
						int GettingTheChances = Math::RandIntMinMax(1, chanceToReact);  // get chance to make devil go to  the pos
						if (GettingTheChances == 1)
						{
							//GameEntity *zeOwner = dynamic_cast<GameEntity*>(owner_of_component);
							GameEntity *zeOwner = dynamic_cast<GameEntity*>(*it);
							DevilReactComponent *devilreact = dynamic_cast<DevilReactComponent*>(&zeOwner->getComponent(DevilReactComponent::ID_));
							if (devilreact->HasReactToMessage == true)
							{
								return false;//alr is reacting
							}
							else
							{
								FSM_ = dynamic_cast<StateMachineComponent*>(&zeOwner->getComponent(StateMachineComponent::ID_.getValue()));
								size_t posOfLastOr = zeEvent.find_last_of("|");
								std::string extractingTheMessage = zeEvent.substr(posOfLastOr + 1); // name of the entity to follw

								FSM_->switchState(0);   // Causing it to switch to target State
								FSM_->onNotify(extractingTheMessage);
								devilreact->HasReactToMessage = true;
								return true;
							}
						}
					}
				}
				//}
				return false;
			}
		}
		else if (zeEvent.find("Devil<LDR>|Zombie&Devil<LDR>") != std::string::npos
			&& zeEvent.find("name") != std::string::npos)
		{
			if (zeEvent.find("I Need Assistance!") != std::string::npos)
			{
				//int GettingTheChances = Math::RandIntMinMax(1, chanceToReact / chanceToReact);  // get chance to make devil go to  the pos
				//if (GettingTheChances == 1) // no need to see chance, if the leader is in need every devil must go
				//{
					//GameEntity *zeOwner = dynamic_cast<GameEntity*>(owner_of_component);
				AllyEnemyComponent *checkOtherDevil = dynamic_cast<AllyEnemyComponent*>(&zeOwnerMain->getComponent(AllyEnemyComponent::ID_));// the the ally list to find all the other devils
				for (std::vector<GameEntity*>::iterator it = checkOtherDevil->m_allyList->begin(), end = checkOtherDevil->m_allyList->end(); it != end; ++it) // iterate 
				{
					if ((*it)->getName().find("Devil") != std::string::npos)//find entities with Devil in the name that is not the  
					{
						//since the sender is the devil leader, the leader will definately call the other devils for help
						GameEntity *zeOwner = dynamic_cast<GameEntity*>(*it);
						FSM_ = dynamic_cast<StateMachineComponent*>(&zeOwner->getComponent(StateMachineComponent::ID_.getValue()));
						size_t posOfLastOr = zeEvent.find_last_of("|");
						std::string extractingTheMessage = zeEvent.substr(posOfLastOr + 1); // name of the entity to follw
						FSM_->switchState(0);   // Causing it to switch to target State
						FSM_->onNotify(extractingTheMessage);
						HasReactToMessage = true;
						return true;
					}
				}
				//}
				//}
				return false;
			}
		}
		return false;
	}
	return false;
}

//bool DevilReactComponent::onNotify(const int &zeEvent)
//{
//	if (zeEvent > 0)
//	{
//		chanceToReact = zeEvent;
//		return true;
//	}
//	return false;
//}

bool DevilReactComponent::onNotify(const int &zeEvent)
{
	switch (zeEvent)
	{
	case 0: // If the event is 0, it means that it has reacted to the message!
		HasReactToMessage = false;
		//std::cout << "Has Responded to that message!" << std::endl;
		return true;
		break;
	case 1:
		HasReactToMessage = true;
		return true;
		break;
	case 100:
		return HasReactToMessage;
		break;
	default:
		break;
	}

	return false;
}