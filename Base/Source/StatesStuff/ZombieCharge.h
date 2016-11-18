#pragma once

#include "StateComponent.h"

class ZombieCharge : public StateComponent
{
public:
    ZombieCharge();
    virtual ~ZombieCharge();

    virtual void Update(double dt);
    virtual void Exit();

    virtual bool onNotify(GenericComponent &zeEvent);
    virtual bool onNotify(const float &zeEvent);
    virtual bool onNotify(const int &zeEvent);

    static const unsigned char ID_ = 5;

protected:
    GenericComponent *zeVictim;
    float originalOwnerSpeed;
    int howManyTimesSpeed;
};