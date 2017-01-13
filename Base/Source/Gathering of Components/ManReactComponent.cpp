#include "ManReactComponent.h"
#include "../Classes/GameEntity.h"
#include "../StatesStuff/StateMachineComponent.h"

ManReactComponent::ManReactComponent()
{
    name_ = "Man Reaction";
    receivedMessage = "";
    FSM_ = nullptr;
    chanceToReact = 1;
}

ManReactComponent::~ManReactComponent()
{

}

bool ManReactComponent::onNotify(const std::string &zeEvent)
{
    if (zeEvent.find("Dog") != std::string::npos && zeEvent.find("Guy") != std::string::npos) // Check and see if this message is meant for the guy
    {
        if (!FSM_)  // This if statement is to check whether FSM pointer has been initialized. if not, find it!
        {
            GameEntity *zeOwner = dynamic_cast<GameEntity*>(owner_of_component);
            FSM_ = dynamic_cast<StateMachineComponent*>(&zeOwner->getComponent(StateMachineComponent::ID_.getValue()));
        }
        if (zeEvent.find("BARK") != std::string::npos)  // Is it the dog barking, if so do the following statements
        {
            size_t posOfLastOr = zeEvent.find_last_of("|");
            std::string extractingTheMessage = zeEvent.substr(posOfLastOr + 1); // Extracting the real content because we don't need the message. In this case, it will be the dog's position
            FSM_->switchState(0);   // Causing it to switch to Patrol State
            return FSM_->onNotify(extractingTheMessage);
        }
        return true;
    }
    return false;
}

bool ManReactComponent::onNotify(const int &zeEvent)
{
    if (zeEvent > 0)
    {
        chanceToReact = zeEvent;
        return true;
    }
    return false;
}