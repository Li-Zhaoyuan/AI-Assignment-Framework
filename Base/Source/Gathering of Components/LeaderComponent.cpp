#include "LeaderComponent.h"

LeaderComponent::LeaderComponent()
{
    name_ = "Leader Component";
    changeLeaderName = false;
    originalName = "";
}

LeaderComponent::~LeaderComponent()
{
    Exit();
}

void LeaderComponent::Init()
{
    changeLeaderName = false;
    originalName = "";
}

void LeaderComponent::Update(double dt)
{

}

void LeaderComponent::Exit()
{
    if (changeLeaderName)   // check whether the name has been changed before. If so, change it back!
    {
        owner_of_component->setName(originalName);
        changeLeaderName = false;
        originalName = "";
    }
}

bool LeaderComponent::onNotify(GenericEntity &zeEvent)
{
    return true;
}

