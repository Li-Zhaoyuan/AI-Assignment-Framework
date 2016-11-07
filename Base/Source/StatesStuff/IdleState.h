#pragma once

#include "StateComponent.h"

class IdleState : public StateComponent
{
public:
    IdleState();
    virtual ~IdleState();

    virtual void Init();
    virtual void Update(double dt);
};