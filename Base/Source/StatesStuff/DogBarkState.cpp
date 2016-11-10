#include "DogBarkState.h"

DogBarkState::DogBarkState()
{
    Init();
}

DogBarkState::~DogBarkState()
{
    Exit();
}

void DogBarkState::Init()
{
    changedName = false;
}

void DogBarkState::Update(double dt)
{
    switch (changedName)
    {
    case false:
    {
        originalOwnerName = owner_of_component->getName();
        std::string zeName = originalOwnerName;
        changedName = true;
    }
    break;
    default:
        break;
    }
}

void DogBarkState::Exit()
{
    changedName = false;
}

