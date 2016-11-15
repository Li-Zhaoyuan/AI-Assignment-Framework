#pragma once

#include "StateComponent.h"
#include "../Classes/GameEntity.h"

class MeleeAttackState : public StateComponent
{
public:
    MeleeAttackState();
    virtual ~MeleeAttackState();

    virtual void Update(double dt);

    static const unsigned char ID_ = 3;

    virtual bool onNotify(const int &zeEvent);

protected:
    GameEntity *zeVictim;
};