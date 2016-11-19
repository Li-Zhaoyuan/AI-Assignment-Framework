#include "SpeedComponent.h"
#include "MyMath.h"

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
    if (zeEvent > Math::EPSILON)
    {
        speed_ = zeEvent;
        return true;
    }
    return false;
}

float &SpeedComponent::getSpeed()
{
    return speed_;
}