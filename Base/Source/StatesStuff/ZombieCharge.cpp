#include "ZombieCharge.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Gathering of Components/SpeedComponent.h"
#include "../Classes/GameEntity.h"
#include "MyMath.h"
#include "MeleeAttackState.h"

ZombieCharge::ZombieCharge()
{
    name_ = "CHARGE";
    changedName = false;
    originalOwnerName = "";
    zeVictim = nullptr;
    originalOwnerSpeed = 0;
    howManyTimesSpeed = 2;
}

ZombieCharge::~ZombieCharge()
{
    Exit();
}

void ZombieCharge::Update(double dt)
{
#ifdef _DEBUG
    assert(zeVictim);
#endif
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

    GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
    PhysicsComponent *zePhysics = dynamic_cast<PhysicsComponent*>(&zeGo->getComponent(PhysicsComponent::g_ID_));
    PhysicsComponent *enemyPhysics = dynamic_cast<PhysicsComponent*>(zeVictim);
    if ((zePhysics->getPos() - enemyPhysics->getPos()).LengthSquared() > influenceRadius * influenceRadius)
    {
        FSM_->switchState(1);
    }
    else
    {
        SpeedComponent *zeSpeed = dynamic_cast<SpeedComponent*>(&zeGo->getComponent(SpeedComponent::ID_));
        Vector3 sqOfDist = enemyPhysics->getPos() - zePhysics->getPos();
        MeleeAttackState *zeMelee = dynamic_cast<MeleeAttackState*>(&FSM_->getSpecificStates(MeleeAttackState::ID_));
        if (sqOfDist.LengthSquared() <= zeMelee->getAttackRadius() * zeMelee->getAttackRadius())
        {
            FSM_->getSpecificStates(MeleeAttackState::ID_).onNotify(*zeVictim);
            FSM_->switchState(MeleeAttackState::ID_);
        }
        else
            zePhysics->setVel(sqOfDist.Normalize() * zeSpeed->getSpeed());
    }
}

void ZombieCharge::Exit()
{
    if (originalOwnerName != "")
        owner_of_component->setName(originalOwnerName);
    changedName = false;
    zeVictim = nullptr;
    GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
    SpeedComponent *zeSpeed = dynamic_cast<SpeedComponent*>(&zeGo->getComponent(SpeedComponent::ID_));
    zeSpeed->onNotify(originalOwnerSpeed);
}

bool ZombieCharge::onNotify(GenericComponent &zeEvent)
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
    GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
    SpeedComponent *zeSpeed = dynamic_cast<SpeedComponent*>(&zeGo->getComponent(SpeedComponent::ID_));
    originalOwnerSpeed = zeSpeed->getSpeed();
    zeSpeed->onNotify(originalOwnerSpeed * howManyTimesSpeed);
    return true;
}

bool ZombieCharge::onNotify(const float &zeEvent)
{
    if (zeEvent > Math::EPSILON)
    {
        influenceRadius = zeEvent;
        return true;
    }
    return false;
}

bool ZombieCharge::onNotify(const int &zeEvent)
{
    if (zeEvent >= 1)
    {
        howManyTimesSpeed = zeEvent;
        return true;
    }
    return false;
}