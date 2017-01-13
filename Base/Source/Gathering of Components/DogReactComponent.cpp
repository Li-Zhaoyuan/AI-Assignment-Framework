#include "DogReactComponent.h"

DogReactComponent::DogReactComponent()
{
    name_ = "Dog Reaction Message";
    receivedMessage = "";
}

DogReactComponent::~DogReactComponent()
{

}

bool DogReactComponent::onNotify(const std::string &zeEvent)
{


    return false;
}