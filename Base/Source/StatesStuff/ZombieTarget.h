#pragma once

#include "StateComponent.h"

class ZombieTarget : public StateComponent
{
public:
    ZombieTarget();
    virtual ~ZombieTarget();

    virtual void Update(double dt);
    virtual void Exit();

    virtual bool onNotify(const float &zeEvent);
    virtual bool onNotify(GenericComponent &zeEvent);

    static const unsigned char ID_ = 1;

protected:
    GenericComponent *zeVictim;
};