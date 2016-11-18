#include "ZombieCharge.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Gathering of Components/SpeedComponent.h"
#include "../Classes/GameEntity.h"
#include "MyMath.h"
#include "MeleeAttackState.h"

ZombieCharge::ZombieCharge()
{
    name_ = "TARGET";
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
}

void ZombieCharge::Exit()
{
    owner_of_component->setName(originalOwnerName);
    changedName = false;
    zeVictim = nullptr;
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
    if (zeEvent > 1)
    {
        howManyTimesSpeed = zeEvent;
        return true;
    }
    return false;
}