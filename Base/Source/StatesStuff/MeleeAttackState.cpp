#include "MeleeAttackState.h"
#include "../Gathering of Components/HPandDPComponent.h"
#include "../Misc/GlobalFunctions.h"
#include "MyMath.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Classes/GameEntity.h"
#include "../Systems/Scene_System.h"

MeleeAttackState::MeleeAttackState()
{
    Init();
}

MeleeAttackState::~MeleeAttackState()
{
    zeVictim = nullptr;
}

void MeleeAttackState::Init()
{
    zeVictim = nullptr;
    influenceRadius = 0;
    attackDelay = 0;
    timeCounter = 0;
    name_ = "MELEE";
    changedName = false;
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
        GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
        PhysicsComponent *zePhysics = dynamic_cast<PhysicsComponent*>(&zeGo->getComponent(PhysicsComponent::g_ID_));
        switch (zePhysics->getVel().IsZero())
        {
        case false:
            zePhysics->getVel().SetZero();
            break;
        default:
            break;
        }
        PhysicsComponent *zeEnemyPhysic = dynamic_cast<PhysicsComponent*>(zeVictim);
        if ((zePhysics->getPos() - zeEnemyPhysic->getPos()).LengthSquared() <= influenceRadius * influenceRadius)
        {
            GameEntity *zeEnemy = dynamic_cast<GameEntity*>(&zeVictim->getOwner());
            HPandDPComponent *enemyHealth = dynamic_cast<HPandDPComponent*>(&zeEnemy->getComponent(HPandDPComponent::ID_));
            HPandDPComponent *zeMyDMG = dynamic_cast<HPandDPComponent*>(&zeGo->getComponent(HPandDPComponent::ID_));
            enemyHealth->onNotify(-zeMyDMG->getDamage());
            if (enemyHealth->getHealth() <= 0) {
                FSM_->switchState(0);
                Scene_System::accessing().getCurrScene().onNotify(*zeEnemy);
            }
            timeCounter = 0;
        }
        else {
            if (checkWhetherTheWordInThatString("Zombie", originalOwnerName))
            {
                FSM_->getSpecificStates(1).onNotify(*zeVictim);
                FSM_->switchState(1);
            }
            else
                FSM_->switchState(0);
        }
    }
}

void MeleeAttackState::Exit()
{
    zeVictim = nullptr; 
    timeCounter = attackDelay;
    changedName = false;
    if (originalOwnerName != "")
        owner_of_component->setName(originalOwnerName);
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
        timeCounter = attackDelay;
        return true;
    }
    return false;
}

bool MeleeAttackState::onNotify(GenericComponent &zeEvent)
{
    PhysicsComponent *zeVictimPhy = dynamic_cast<PhysicsComponent*>(&zeEvent);
    if (zeVictimPhy)
    {
        zeVictim = zeVictimPhy;
    }
    else
    {
        GameEntity *zeVictimEntity = dynamic_cast<GameEntity*>(&zeEvent.getOwner());
        zeVictim = dynamic_cast<PhysicsComponent*>(&zeVictimEntity->getComponent(PhysicsComponent::g_ID_));
    }
    timeCounter = attackDelay;
    return true;
}

float &MeleeAttackState::getAttackRadius()
{
    return influenceRadius;
}