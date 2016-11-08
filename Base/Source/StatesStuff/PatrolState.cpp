#include "PatrolState.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Classes/GameEntity.h"
#include "../Gathering of Components/SpeedComponent.h"

PatrolState::PatrolState()
{
    Init();
}

PatrolState::~PatrolState()
{
    boundaryOfThePlace = nullptr;
}

void PatrolState::Init()
{
    boundaryOfThePlace = nullptr;
    hasChangedName = isMovingTowardsThatPos = false;
    originalOwnerName = "";
    name_ = "PATROL";
}

void PatrolState::Update(double dt)
{
    switch (hasChangedName)
    {
    case false:
    {
        std::string zeName = owner_of_component->getName();
        originalOwnerName = zeName;
        zeName.append(name_);
        owner_of_component->setName(zeName);
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
        //SpeedComponent *zeSpeed = dynamic_cast<SpeedComponent*>(&zeGO->getComponent(SpeedComponent::ID_));

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
    owner_of_component->setName(originalOwnerName);
}