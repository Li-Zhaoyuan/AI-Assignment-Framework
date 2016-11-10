#pragma once

#include "StateComponent.h"

class DogBarkState : public StateComponent
{
public:
    DogBarkState();
    virtual ~DogBarkState();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Exit();

protected:
    bool warnedEveryone;
};