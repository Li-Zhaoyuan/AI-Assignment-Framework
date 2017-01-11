#include "ManReactComponent.h"

ManReactComponent::ManReactComponent()
{
    name_ = "Man Reaction";
    receivedMessage = "";
}

ManReactComponent::~ManReactComponent()
{

}

bool ManReactComponent::onNotify(const std::string &zeEvent)
{
    if (zeEvent.find("Dog") != std::string::npos)
    {
        return true;
    }
    return false;
}