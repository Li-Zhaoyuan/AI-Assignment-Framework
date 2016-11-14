#include "DogBarkState.h"
#include "../Classes/GameEntity.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include <sstream>
#include "MyMath.h"

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
    warnedEveryone = false;
    name_ = "BARK";
}

void DogBarkState::Update(double dt)
{
    switch (changedName)
    {
    case false:
    {
        originalOwnerName = owner_of_component->getName();
        std::string zeName = originalOwnerName;
        zeName.append(name_);
        owner_of_component->setName(zeName);
        changedName = true;
    }
    break;
    default:
        break;
    }
    GameEntity *zeOwner = dynamic_cast<GameEntity*>(owner_of_component);
    PhysicsComponent *zePhysics = dynamic_cast<PhysicsComponent*>(&zeOwner->getComponent(PhysicsComponent::g_ID_));
    AllyEnemyComponent *zeEnemyList = dynamic_cast<AllyEnemyComponent*>(&zeOwner->getComponent(AllyEnemyComponent::ID_));
    std::ostringstream ss;
    switch (warnedEveryone)
    {
    case false:
    {
        for (std::vector<GameEntity*>::iterator it = zeEnemyList->m_enemyList->begin(), end = zeEnemyList->m_enemyList->end(); it != end; ++it)
        {
            StateMachineComponent *zeFSM = dynamic_cast<StateMachineComponent*>(&(*it)->getComponent(StateMachineComponent::ID_.getValue()));
            zeFSM->switchState(2);
            ss.str("");
            ss << "GO:" << zePhysics->getPos().x << "," << zePhysics->getPos().y << "," << zePhysics->getPos().z;
            zeFSM->getCurrentState().onNotify(ss.str());
        }
    }
        warnedEveryone = true;
        break;
    default:
    {
        for (std::vector<GameEntity*>::iterator it = zeEnemyList->m_enemyList->begin(), end = zeEnemyList->m_enemyList->end(); it != end; ++it)
        {
            PhysicsComponent *enemyPhy = dynamic_cast<PhysicsComponent*>(&(*it)->getComponent(PhysicsComponent::g_ID_));
            Vector3 theDistBetweenYouAndEnemy = (zePhysics->getPos() - enemyPhy->getPos());
            if (theDistBetweenYouAndEnemy.LengthSquared() <= (toRunAway * toRunAway))
            {
                theDistBetweenYouAndEnemy.Normalized();
                FSM_->switchState(2);            
                ss << "GO:" << theDistBetweenYouAndEnemy.x * 50 << "," << theDistBetweenYouAndEnemy.y * 50 << "," << 0;
                FSM_->getCurrentState().onNotify(ss.str());
                break;
            }
        }
    }
    break;
    }
}

void DogBarkState::Exit()
{
    changedName = false;
    warnedEveryone = false;
    owner_of_component->setName(originalOwnerName);
}

bool DogBarkState::onNotify(const float &zeEvent)
{
    if (zeEvent > Math::EPSILON)
    {
        toRunAway = zeEvent;
        return true;
    }
    return false;
}