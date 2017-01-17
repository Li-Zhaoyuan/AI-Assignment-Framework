#include "DogReactComponent.h"
#include "../StatesStuff/StateMachineComponent.h"
#include "../Classes/GameEntity.h"
#include "AllyEnemyComponent.h"

DogReactComponent::DogReactComponent()
{
    name_ = "Dog Reaction Message";
    receivedMessage = "";
    FSM_ = nullptr;
    listOfAllyEnemy = nullptr;
    HasReactedToMessage = false;
}

DogReactComponent::~DogReactComponent()
{

}

bool DogReactComponent::onNotify(const std::string &zeEvent)
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
    if (TextMessage.find("I am being attacked") != std::string::npos && FromMessage.find("Guy") != std::string::npos)   // checking whether is it the correct string
    {
        std::string contentMessage = thirdPart.substr(thirdOR + 1); // "CONTENT"
        FSM_->switchState(2);
        return FSM_->onNotify(contentMessage);
    }
    return false;
}