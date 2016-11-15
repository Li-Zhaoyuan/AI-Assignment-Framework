#pragma once

#include "StateComponent.h"

class MeleeAttackState : public StateComponent
{
public:
    MeleeAttackState();
    virtual ~MeleeAttackState();

    virtual void Update(double dt);

    static const unsigned char ID_ = 3;
};