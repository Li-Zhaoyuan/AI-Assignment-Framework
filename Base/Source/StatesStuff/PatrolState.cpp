#include "PatrolState.h"
#include "../Gathering of Components/PhysicsComponent.h"

PatrolState::PatrolState()
{
    Init();
    name_ = "PATROL";
}

PatrolState::~PatrolState()
{
    boundaryOfThePlace = nullptr;
}

void PatrolState::Init()
{
    boundaryOfThePlace = nullptr;
    hasChangedName = false;
}

void PatrolState::Update(double dt)
{
    switch (hasChangedName)
    {
    case false:
    {
        std::string zeName = owner_of_component->getName();
        zeName.append(name_);
        owner_of_component->setName(name_);
        hasChangedName = true;
    }
    break;
    default:
        break;
    }
}

void PatrolState::Exit()
{
    hasChangedName = false;
}