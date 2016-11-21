#pragma once

#include "StateComponent.h"

class DogBite : public StateComponent
{
public:
    DogBite();
    virtual ~DogBite();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Exit();

    static const unsigned char ID_ = 3;

    virtual bool onNotify(GenericComponent &zeEvent);
    virtual bool onNotify(const int &zeEvent);
    virtual bool onNotify(const float &zeEvent);

protected:
    float timeCounter, attackDelay;
    int chanceToActivate;
    GenericComponent *zeVictim;
};