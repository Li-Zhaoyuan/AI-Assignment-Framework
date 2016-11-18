#pragma once

#include "StateComponent.h"

class ZombieCharge : public StateComponent
{
public:
    ZombieCharge();
    virtual ~ZombieCharge();

    virtual void Update(double dt);
    virtual void Exit();

    static const unsigned char ID_ = 5;
};