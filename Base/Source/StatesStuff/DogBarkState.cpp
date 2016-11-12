#include "DogBarkState.h"
#include "../Classes/GameEntity.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include <sstream>

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
    switch (warnedEveryone)
    {
    case false:
    {
        GameEntity *zeOwner = dynamic_cast<GameEntity*>(owner_of_component);
        PhysicsComponent *zePhysics = dynamic_cast<PhysicsComponent*>(&zeOwner->getComponent(PhysicsComponent::g_ID_));
        AllyEnemyComponent *zeEnemyList = dynamic_cast<AllyEnemyComponent*>(&zeOwner->getComponent(AllyEnemyComponent::ID_));
        std::ostringstream ss;
        for (std::vector<GameEntity*>::iterator it = zeEnemyList->m_enemyList->begin(), end = zeEnemyList->m_enemyList->end(); it != end; ++it)
        {
            StateMachineComponent *zeFSM = dynamic_cast<StateMachineComponent*>(&(*it)->getComponent(StateMachineComponent::ID_.getValue()));
            ss.str("");
            ss << "GO:" << zePhysics->getPos().x << "," << zePhysics->getPos().y << "," << zePhysics->getPos().z;
            zeFSM->getCurrentState().onNotify(ss.str());
        }
    }
        warnedEveryone = true;
        break;
    default:
        break;
    }
}

void DogBarkState::Exit()
{
    changedName = false;
    warnedEveryone = false;
}

