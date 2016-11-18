#include "ZombieTarget.h"
#include "MyMath.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Classes/GameEntity.h"

ZombieTarget::ZombieTarget()
{
    name_ = "TARGET";
    changedName = false;
    originalOwnerName = "";
    chancesOfAction = 0;
}

ZombieTarget::~ZombieTarget()
{
    Exit();
}

void ZombieTarget::Update(double dt)
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
    GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
    PhysicsComponent *zePhysics = dynamic_cast<PhysicsComponent*>(&zeGo->getComponent(PhysicsComponent::g_ID_));
    PhysicsComponent *enemyPhysics = dynamic_cast<PhysicsComponent*>(zeVictim);
    if ((zePhysics->getPos() - enemyPhysics->getPos()).LengthSquared() > influenceRadius * influenceRadius)
    {
        FSM_->switchState(0);
    }
    else
    {

    }
}

void ZombieTarget::Exit()
{
    zeVictim = nullptr;
    changedName = false;
    owner_of_component->setName(originalOwnerName);
}

bool ZombieTarget::onNotify(const float &zeEvent)
{
    if (zeEvent > Math::EPSILON)
    {
        influenceRadius = zeEvent;
        return true;
    }
    return false;
}

bool ZombieTarget::onNotify(GenericComponent &zeEvent)
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

bool ZombieTarget::onNotify(const int &zeEvent)
{
    if (zeEvent > 0)
    {
        chancesOfAction = zeEvent;
    }
    return false;
}