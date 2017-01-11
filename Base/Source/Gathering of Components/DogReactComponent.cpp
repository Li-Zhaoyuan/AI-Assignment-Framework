#include "DogReactComponent.h"

DogReactComponent::DogReactComponent()
{
    name_ = "Dog Reaction Message";
    receivedMessage = "";
}

DogReactComponent::~DogReactComponent()
{

}

void DogReactComponent::Update(double dt)
{

}

bool DogReactComponent::onNotify(const std::string &zeEvent)
{


    return false;
}