#include "ManReactComponent.h"
#include "../Classes/GameEntity.h"
#include "../StatesStuff/StateMachineComponent.h"
#include "MyMath.h"
#include "AllyEnemyComponent.h"
#include "../Systems/MessageSystem.h"
#include <iostream>

ManReactComponent::ManReactComponent()
{
    name_ = "Man Reaction";
    receivedMessage = "";
    FSM_ = nullptr;
    chanceToReact = 2;
    listOfAllyEnemy = nullptr;
    HasReactToMessage = false;
}

ManReactComponent::~ManReactComponent()
{

}

bool ManReactComponent::onNotify(const std::string &zeEvent)
{
    if (!FSM_)
    {
        GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
        FSM_ = dynamic_cast<StateMachineComponent*>(&zeGo->getComponent(StateMachineComponent::ID_.getValue()));
    }
    if (!listOfAllyEnemy)
    {
        GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
        listOfAllyEnemy = dynamic_cast<AllyEnemyComponent*>(&zeGo->getComponent(AllyEnemyComponent::ID_));
    }
    
    size_t firstOR = zeEvent.find("|"); // Get the message because the string is in the Format of "MESSAGE|FROM|TO|CONTENT"
    std::string TextMessage = zeEvent.substr(0, firstOR);
    std::string secondPart = zeEvent.substr(firstOR + 1);   // Here shall be "FROM|TO|CONTENT....."
    size_t secondOR = secondPart.find("|");

    std::string FromMessage = secondPart.substr(0, secondOR);
    std::string thirdPart = secondPart.substr(secondOR + 1);   // "TO|CONTENT"

    size_t thirdOR = thirdPart.find("|");
    std::string ToMessage = thirdPart.substr(0, thirdOR);
    if (FromMessage.find("Dog") != std::string::npos && thirdPart.find("Guy") != std::string::npos) // Check and see if this message is meant for the guy
    {
        if (TextMessage.find("BARK") != std::string::npos)  // Is it the dog barking, if so do the following statements
        {
            GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
            if (zeGo->seeComponentActive(11))   // see if am I the leader.
            {
                int GettingTheChances = Math::RandIntMinMax(1, chanceToReact);  // Giving the chance for man to react properly.
                if (GettingTheChances == 1)
                {
                    size_t posOfLastOr = zeEvent.find_last_of("|");
                    std::string extractingTheMessage = zeEvent.substr(posOfLastOr + 1); // Extracting the real content because we don't need the message. In this case, it will be the dog's position
                    return MessageSystem::accessing().onNotify("Help Dog|LEADER|Guy|"+extractingTheMessage);    // Sending the message to message board so other guys will be able to listen to it!
                }
            }
            else
                return false;
        }
        return true;
    }
    else if (FromMessage == "LEADER" && ToMessage == "Guy" && TextMessage == "Help Dog") // Checking whether the message is from the Leader and sending to Guy
    {
        size_t posOfLastOr = zeEvent.find_last_of("|");
        std::string extractingTheMessage = zeEvent.substr(posOfLastOr + 1); // Extracting the real content because we don't need the message. In this case, it will be the dog's position
        FSM_->switchState(0);   // Causing it to switch to Patrol State
        //std::cout << owner_of_component->getName() << " Helping the dog!" << std::endl; // need to check if this has been passed through or not
        return FSM_->onNotify(extractingTheMessage);
    }
    // These parts will check to see if the guys is being attacked or not
    else if (TextMessage.find("I am being attacked") != std::string::npos && FromMessage.find("Guy") != std::string::npos)  // This will help to check if it is a message from the guy.
    {
        GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
        if (zeGo->seeComponentActive(11))   // see if am I the leader. Else ignore the message
        {
            int GettingTheChances = Math::RandIntMinMax(1, chanceToReact);  // Giving the chance for man to react properly.
            if (GettingTheChances == 1)
            {
                size_t posOfLastOr = zeEvent.find_last_of("|");
                std::string extractingTheMessage = zeEvent.substr(posOfLastOr + 1); // Extracting the real content because we don't need the message. In this case, it will be the guys's position
                return MessageSystem::accessing().onNotify("Help Guy|LEADER|Guy|" + extractingTheMessage);    // Sending the message to message board so other guys will be able to listen to it!
            }
            return true;
        }
    }
    else if (FromMessage == "LEADER" && ToMessage == "Guy" && TextMessage == "Help Guy") // Checking whether the message is from the Leader and sending to Guy
    {
        size_t posOfLastOr = zeEvent.find_last_of("|");
        std::string extractingTheMessage = zeEvent.substr(posOfLastOr + 1); // Extracting the real content because we don't need the message. In this case, it will be the dog's position
        FSM_->switchState(0);   // Causing it to switch to Patrol State
        //std::cout << owner_of_component->getName() << " helping guy" << std::endl;
        return FSM_->onNotify(extractingTheMessage);
    }
        // These parts will check to see if the guys is being attacked or not
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