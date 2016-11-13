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

    static const unsigned char ID_ = 1;

protected:
    bool warnedEveryone;
};