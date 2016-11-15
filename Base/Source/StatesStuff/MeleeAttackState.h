#pragma once

#include "StateComponent.h"
#include "../Classes/GameEntity.h"

class MeleeAttackState : public StateComponent
{
public:
    MeleeAttackState();
    virtual ~MeleeAttackState();

    virtual void Update(double dt);
    virtual void Exit();

    static const unsigned char ID_ = 3;

    virtual bool onNotify(const std::string &zeEvent);
    virtual bool onNotify(const float &zeEvent);

protected:
    GameEntity *zeVictim;
    float influenceRadius;
};