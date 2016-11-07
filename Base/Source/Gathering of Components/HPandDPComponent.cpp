#include "HPandDPComponent.h"

HPandDPComponent::HPandDPComponent()
{
    Init();
}

HPandDPComponent::HPandDPComponent(const int &zeHealth, const int &zeDMG)
{
    health_ = zeHealth;
    damage_ = zeDMG;
}

HPandDPComponent::~HPandDPComponent()
{

}

void HPandDPComponent::Init()
{
    health_ = 0; 
    damage_ = 0;
}

void HPandDPComponent::setDamage(const int &zeDMG)
{
    damage_ = zeDMG;
}

void HPandDPComponent::setHealth(const int &zeHealth)
{
    health_ = zeHealth;
}

bool HPandDPComponent::onNotify(const int &zeEvent)
{
    health_ += zeEvent;
    return true;
}

int &HPandDPComponent::getDamage()
{
    return damage_;
}

int &HPandDPComponent::getHealth()
{
    return health_;
}