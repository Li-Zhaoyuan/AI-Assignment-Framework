#pragma once

#include "StateComponent.h"

class MeleeAttackState : public StateComponent
{
private:
    friend  GenericComponent;
public:
    MeleeAttackState();
    virtual ~MeleeAttackState();

    virtual void Update(double dt);
    virtual void Exit();

    static const unsigned char ID_ = 3;

    virtual bool onNotify(const float &zeEvent);
    virtual bool onNotify(GenericComponent &zeEvent);

    float &getAttackRadius();

protected:
    GenericComponent *zeVictim;
    float attackDelay, timeCounter;
};