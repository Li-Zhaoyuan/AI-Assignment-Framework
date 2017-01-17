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
    if (!changeLeaderName)
    {
        originalName = owner_of_component->getName();
        owner_of_component->setName(originalName + "<LEADER>");
        changeLeaderName = true;
    }
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
