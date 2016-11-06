#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent()
{

}

PhysicsComponent::~PhysicsComponent()
{

}

void PhysicsComponent::Update(double dt)
{

}

Vector3 &PhysicsComponent::getAccel()
{
    return accel_;
}

Vector3 &PhysicsComponent::getVel()
{
    return vel_;
}

Vector3 &PhysicsComponent::getPos()
{
    return pos_;
}

Vector3 &PhysicsComponent::getSize()
{
    return size_;
}