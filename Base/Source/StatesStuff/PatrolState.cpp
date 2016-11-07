#include "PatrolState.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Classes/GameEntity.h"

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
    hasChangedName = isMovingTowardsThatPos = false;
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
    GameEntity *zeGO = dynamic_cast<GameEntity*>(owner_of_component);
    PhysicsComponent *zePhysic = dynamic_cast<PhysicsComponent*>(&zeGO->getComponent(PhysicsComponent::g_ID_));
    switch (isMovingTowardsThatPos)
    {
    case false:
    {
        isMovingTowardsThatPos = true;
    }
        break;
    default:
        break;
    }
}

void PatrolState::Exit()
{
    hasChangedName = false;
    isMovingTowardsThatPos = false;
}