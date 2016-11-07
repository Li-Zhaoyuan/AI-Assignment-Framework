#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent()
{
    Init();
}

PhysicsComponent::~PhysicsComponent()
{

}

void PhysicsComponent::Init()
{
    size_.Set(1, 1, 1);
    accel_.SetZero();
    pos_.SetZero();
    vel_.SetZero();
    rotationY = 0;
}

void PhysicsComponent::Update(double dt)
{
    switch (accel_.IsZero())
    {
    case false:
        vel_ += accel_ * (float)(dt);
        break;
    default:
        break;
    }
    switch (vel_.IsZero())
    {
    case false:
        pos_ += vel_ * (float)(dt);
        break;
    default:
        break;
    }
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

void PhysicsComponent::setPos(const Vector3 &zePos)
{
    pos_.Set(zePos.x, zePos.y, zePos.z);
}

void PhysicsComponent::setSize(const Vector3 &zeSize)
{
    size_.Set(zeSize.x, zeSize.y, zeSize.z);
}

void PhysicsComponent::setVel(const Vector3 &zeVel)
{
    vel_.Set(zeVel.x, zeVel.y, zeVel.z);
}

void PhysicsComponent::setAccel(const Vector3 &zeAccel)
{
    accel_.Set(zeAccel.x, zeAccel.y, zeAccel.z);
}

void PhysicsComponent::setYrotation(const float &zeVal)
{
    rotationY = zeVal;
}

float &PhysicsComponent::getYrotation()
{
    return rotationY;
}