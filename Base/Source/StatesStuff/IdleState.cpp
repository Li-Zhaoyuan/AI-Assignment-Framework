#include "IdleState.h"
#include "../Misc/GlobalFunctions.h"
#include "MyMath.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../Gathering of Components/PhysicsComponent.h"

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
    changedName = false;
    originalOwnerName = "";
}

void IdleState::Update(double dt)
{
    switch (changedName)
    {
    case false:
    {
        std::string newName = owner_of_component->getName();
        originalOwnerName = newName;
        newName.append(name_);
        owner_of_component->setName(newName);
        changedName = true;
    }
        break;
    default:
        break;
    }
    GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
    PhysicsComponent *zePhysics = dynamic_cast<PhysicsComponent*>(&zeGo->getComponent(PhysicsComponent::g_ID_));
    AllyEnemyComponent *zeEnemyStuff = dynamic_cast<AllyEnemyComponent*>(&zeGo->getComponent(AllyEnemyComponent::ID_));
    for (std::vector<GameEntity*>::iterator it = zeEnemyStuff->m_enemyList->begin(), end = zeEnemyStuff->m_enemyList->end(); it != end; ++it)
    {
        GameEntity *zeEnemy = (*it);
        if (zeEnemy->seeComponentActive(4))
        {
            PhysicsComponent *enemyPhy = dynamic_cast<PhysicsComponent*>(&(*it)->getComponent(PhysicsComponent::g_ID_));
            if ((zePhysics->getPos() - enemyPhy->getPos()).LengthSquared() <= influenceRadius * influenceRadius)
            {
                FSM_->switchState(1);
                FSM_->getCurrentState().onNotify(*enemyPhy);
                break;
            }
        }
    }
}

void IdleState::Exit()
{
    changedName = false;
    if (originalOwnerName != "")
        owner_of_component->setName(originalOwnerName);
}

bool IdleState::onNotify(const float &zeEvent)
{
    if (zeEvent > Math::EPSILON)
    {
        influenceRadius = zeEvent;
    }
    return false;
}