#include "IdleState.h"


IdleState::IdleState()
{
    Init();
}

IdleState::~IdleState()
{

}

void IdleState::Init()
{
    name_ = "IDLE";
    hasNameChange = false;
    originalOwnerName = "";
}

void IdleState::Update(double dt)
{
    switch (hasNameChange)
    {
    case false:
    {
        std::string newName = owner_of_component->getName();
        originalOwnerName = newName;
        newName.append(name_);
        owner_of_component->setName(newName);
        hasNameChange = true;
    }
        break;
    default:
        break;
    }
}

void IdleState::Exit()
{
    hasNameChange = false;
    owner_of_component->setName(originalOwnerName);
}