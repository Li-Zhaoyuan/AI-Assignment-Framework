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
}

void PatrolState::Init()
{
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
        while (true)
        {
            int randomNum = 9; 
            float theAngleToGo = 36;
            float theRadianAngle = Math::DegreeToRadian((Math::RandIntMinMax(0, randomNum) * theAngleToGo));
            goToThatPoint.Set(zePhysic->getPos().x + (50 * cos(theRadianAngle)), zePhysic->getPos().y + (50 * sin(theRadianAngle)), zePhysic->getPos().z);
            if (
                goToThatPoint.x < zePhysic->getBoundary().x && goToThatPoint.x > -zePhysic->getBoundary().x
                && goToThatPoint.y < zePhysic->getBoundary().y && goToThatPoint.y > -zePhysic->getBoundary().y
                )
            {
                zePhysic->setVel((goToThatPoint - zePhysic->getPos()).Normalize() * 15);
                break;
            }
        }
        isMovingTowardsThatPos = true;
    }
        break;
    default:
        if ((goToThatPoint - zePhysic->getPos()).LengthSquared() < 4.f)
            isMovingTowardsThatPos = false;
        break;
    }
}

void PatrolState::Exit()
{
    hasChangedName = false;
    isMovingTowardsThatPos = false;
    owner_of_component->setName(originalOwnerName);
}