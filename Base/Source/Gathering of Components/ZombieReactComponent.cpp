#include "ZombieReactComponent.h"
#include "../Classes/GameEntity.h"
#include "../StatesStuff/StateMachineComponent.h"
#include "AllyEnemyComponent.h"
#include "MyMath.h"

ZombieReactComponent::ZombieReactComponent()
{
	name_ = "Zombie Reaction";
	receivedMessage = "";
	FSM_ = nullptr;
	chanceToReact = 2;
	HasReactToMessage = false;
}

ZombieReactComponent::~ZombieReactComponent()
{

}

bool ZombieReactComponent::onNotify(const std::string &zeEvent)
{
	//msg in the format of MESSAGE|SENDER|RECIEVER|GO:
	//I’m Low Health!|Devil|Zombie&Devil<LDR>|name:
	
	if (HasReactToMessage == false)
	{
		if (zeEvent.find("Devil") != std::string::npos//from
			&& zeEvent.find("Zombie") != std::string::npos//reciever
			&& (zeEvent.find("Devil") < zeEvent.find("Zombie")) // making sure the msg is the correct sender and meant for the correct person
			&& zeEvent.find("name") != std::string::npos) // name of the entity the zombie should target
		{
			if (!FSM_)// check if FSM_ is nullptr, if it is assign. initialise :V
			{
				GameEntity *zeOwner = dynamic_cast<GameEntity*>(owner_of_component);
				FSM_ = dynamic_cast<StateMachineComponent*>(&zeOwner->getComponent(StateMachineComponent::ID_.getValue()));
			}
			if (zeEvent.find("I Need Assistance!") != std::string::npos)
			{
				GameEntity *zeOwner = dynamic_cast<GameEntity*>(owner_of_component);
				size_t posOfLastOr = zeEvent.find_last_of("|");
				std::string extractingTheMessage = zeEvent.substr(posOfLastOr + 1); // name of the entity to follw
				//int GettingTheChances = Math::RandIntMinMax(1, chanceToReact);  // Giving the chance for man to react properly.
				//if (GettingTheChances == 1)//zombie no need to think :V just do only
				//{
				FSM_->switchState(1);   // Causing it to switch to target State
				HasReactToMessage = true;
				return FSM_->onNotify(extractingTheMessage);
				//}
				return true;
			}
		}
		return false;
	}
	else if (HasReactToMessage && (zeEvent.find("Devil<LDR>") < zeEvent.find("Zombie"))) // making sure the msg is the correct sender and meant for the correct person)
	{
		if (zeEvent.find("Devil") != std::string::npos//from
			&& zeEvent.find("Zombie") != std::string::npos//reciever
			&& (zeEvent.find("Devil") < zeEvent.find("Zombie")) // making sure the msg is the correct sender and meant for the correct person
			&& zeEvent.find("name") != std::string::npos) // name of the entity the zombie should target
		{
			if (!FSM_)// check if FSM_ is nullptr, if it is assign. initialise :V
			{
				GameEntity *zeOwner = dynamic_cast<GameEntity*>(owner_of_component);
				FSM_ = dynamic_cast<StateMachineComponent*>(&zeOwner->getComponent(StateMachineComponent::ID_.getValue()));
			}
			if (zeEvent.find("I Need Assistance!") != std::string::npos)
			{
				GameEntity *zeOwner = dynamic_cast<GameEntity*>(owner_of_component);
				size_t posOfLastOr = zeEvent.find_last_of("|");
				std::string extractingTheMessage = zeEvent.substr(posOfLastOr + 1); // name of the entity to follw
				//int GettingTheChances = Math::RandIntMinMax(1, chanceToReact);  // Giving the chance for man to react properly.
				//if (GettingTheChances == 1)//zombie no need to think :V just do only
				//{
				FSM_->switchState(1);   // Causing it to switch to target State
				HasReactToMessage = true;
				return FSM_->onNotify(extractingTheMessage);
				//}
				return true;
			}
		}
		return false;
	}
	return false;
}

bool ZombieReactComponent::onNotify(const int &zeEvent)
{
	/*if (zeEvent > 0)
	{
		chanceToReact = zeEvent;
		return true;
	}
	return false;*/
	switch (zeEvent)
	{
	case 0: // If the event is 0, it means that it has reacted to the message!
		HasReactToMessage = false;
		//std::cout << "Has Responded to that message!" << std::endl;
		return true;
		break;
	default:
		break;
	}

	return false;
}