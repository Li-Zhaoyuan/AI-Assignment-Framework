#pragma once

#include "../GenericECS/GenericComponent.h"
#include "Vector3.h"

class PhysicsComponent : public GenericComponent
{
public:
    PhysicsComponent();
    virtual ~PhysicsComponent();

    virtual void Update(double dt);

    Vector3 &getAccel();
    Vector3 &getVel();
    Vector3 &getPos();
    Vector3 &getSize();

private:
    Vector3 accel_, vel_, pos_, size_;
};