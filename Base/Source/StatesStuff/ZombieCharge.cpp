#include "ZombieCharge.h"

ZombieCharge::ZombieCharge()
{
    name_ = "TARGET";
    changedName = false;
    originalOwnerName = "";
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
}