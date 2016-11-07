#pragma once

#include "../GenericECS/GenericComponent.h"
#include "Vector3.h"

class PhysicsComponent : public GenericComponent
{
public:
    PhysicsComponent();
    virtual ~PhysicsComponent();

    virtual void Init();
    virtual void Update(double dt);

    void setPos(const Vector3 &zePos);
    void setSize(const Vector3 &zeSize);
    void setVel(const Vector3 &zeVel);
    void setAccel(const Vector3 &zeAccel);
    void setYrotation(const float &zeVal);

    Vector3 &getAccel();
    Vector3 &getVel();
    Vector3 &getPos();
    Vector3 &getSize();
    float &getYrotation();
    const static unsigned short g_ID_ = 2;

private:
    Vector3 accel_, vel_, pos_, size_;
    float rotationY;
};