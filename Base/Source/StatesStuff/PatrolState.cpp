#include "PatrolState.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Classes/GameEntity.h"
#include "../Gathering of Components/SpeedComponent.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include <sstream>
#include "../Misc/GlobalFunctions.h"

PatrolState::PatrolState()
{
    Init();
}

PatrolState::~PatrolState()
{
}

void PatrolState::Init()
{
    changedName = isMovingTowardsThatPos = false;
    originalOwnerName = "";
    name_ = "PATROL";
    influenceRadius = 0;
}

void PatrolState::Update(double dt)
{
    switch (changedName)
    {
    case false:
    {
        std::string zeName = owner_of_component->getName();
        originalOwnerName = zeName;
        zeName.append(name_);
        owner_of_component->setName(zeName);
        changedName = true;
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
        else
        {
            AllyEnemyComponent *checkForEnemy = dynamic_cast<AllyEnemyComponent*>(&zeGO->getComponent(AllyEnemyComponent::ID_));
            for (std::vector<GameEntity*>::iterator it = checkForEnemy->m_enemyList->begin(), end = checkForEnemy->m_enemyList->end(); it != end; ++it)
            {
                PhysicsComponent *zeEnemyPhysics = dynamic_cast<PhysicsComponent*>(&(*it)->getComponent(PhysicsComponent::g_ID_));
                if ((zeEnemyPhysics->getPos() - zePhysic->getPos()).LengthSquared() <= influenceRadius * influenceRadius)
                {
                    if (checkWhetherTheWordInThatString("Dog", originalOwnerName))
                    {
                        zePhysic->setVel(Vector3(0, 0, 0));
                        FSM_->switchState(1);
                    }
                    break;
                }
            }
        }
        break;
    }
}

void PatrolState::Exit()
{
    changedName = false;
    isMovingTowardsThatPos = false;
    owner_of_component->setName(originalOwnerName);
}

void PatrolState::setInfluenceRadius(const float &zeRadius)
{
    influenceRadius = zeRadius;
}

bool PatrolState::onNotify(const float &zeEvent)
{
    if (zeEvent > 0)
    {
        influenceRadius = zeEvent;
        return true;
    }
    return false;
}