#include "MeleeAttackState.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../Gathering of Components/HPandDPComponent.h"
#include "../Misc/GlobalFunctions.h"
#include "MyMath.h"

MeleeAttackState::MeleeAttackState()
{
    zeVictim = nullptr;
    influenceRadius = 0;
    attackDelay = 0;
    timeCounter = 0;
}

MeleeAttackState::~MeleeAttackState()
{
    zeVictim = nullptr;
}

void MeleeAttackState::Update(double dt)
{
#ifdef _DEBUG
    assert(zeVictim);
#endif
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
    timeCounter += (float)dt;
    if (timeCounter >= attackDelay)
    {
        timeCounter = 0;
    }
}

void MeleeAttackState::Exit()
{
    zeVictim = nullptr; 
    timeCounter = attackDelay;
    changedName = false;
    owner_of_component->setName(originalOwnerName);
}

bool MeleeAttackState::onNotify(const std::string &zeEvent)
{
    GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
    AllyEnemyComponent *zeEnemyAlly = dynamic_cast<AllyEnemyComponent*>(&zeGo->getComponent(AllyEnemyComponent::ID_));
    for (std::vector<GameEntity*>::iterator it = zeEnemyAlly->m_enemyList->begin(), end = zeEnemyAlly->m_enemyList->end(); it != end; ++it)
    {
        if (checkWhetherTheWordInThatString(zeEvent, (*it)->getName()))
        {
            zeVictim = (*it);
            return true;
            break;
        }
    }
    return false;
}

bool MeleeAttackState::onNotify(const float &zeEvent)
{
    if (zeEvent > Math::EPSILON)
    {
        influenceRadius = zeEvent;
        return true;
    }
    else if (zeEvent < -Math::EPSILON)
    {
        attackDelay = -zeEvent;
        return true;
    }
    return false;
}