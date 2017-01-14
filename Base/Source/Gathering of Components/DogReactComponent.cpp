#include "DogReactComponent.h"
#include "../StatesStuff/StateMachineComponent.h"
#include "../Classes/GameEntity.h"

DogReactComponent::DogReactComponent()
{
    name_ = "Dog Reaction Message";
    receivedMessage = "";
    FSM_ = nullptr;
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

    size_t firstOR = zeEvent.find("|"); // Get the message because the string is in the Format of "MESSAGE|FROM|TO|CONTENT"
    std::string TextMessage = zeEvent.substr(0, firstOR);
    std::string secondPart = zeEvent.substr(firstOR + 1);   // Here shall be "FROM|TO|CONTENT....."
    size_t secondOR = secondPart.find("|");

    std::string FromMessage = secondPart.substr(0, secondOR);
    std::string thirdPart = secondPart.substr(secondOR + 1);   // "TO|CONTENT"

    size_t thirdOR = thirdPart.find("|");
    std::string ToMessage = thirdPart.substr(0, thirdOR);
    if (TextMessage == "I am being attacked" && FromMessage == "Guy")
    {
        std::string contentMessage = thirdPart.substr(thirdOR + 1); // "CONTENT"
        return true;
    }
    return false;
}