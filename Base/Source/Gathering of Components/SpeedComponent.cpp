#include "SpeedComponent.h"

SpeedComponent::SpeedComponent()
{
    Init();
}

SpeedComponent::~SpeedComponent()
{

}

void SpeedComponent::Init()
{
    speed_ = 0;
}

bool SpeedComponent::onNotify(const float &zeEvent)
{
    speed_ = zeEvent;
    return true;
}

float &SpeedComponent::getSpeed()
{
    return speed_;
}