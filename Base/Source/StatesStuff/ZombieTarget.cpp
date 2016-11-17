#include "ZombieTarget.h"
#include "MyMath.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Classes/GameEntity.h"

ZombieTarget::ZombieTarget()
{
    name_ = "TARGET";
    changedName = false;
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