#pragma once

#include "StateComponent.h"
#include "Vector3.h"

class PatrolState : public StateComponent
{
public:
    PatrolState();
    virtual ~PatrolState();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Exit();

    static const unsigned char ID_ = 0;

    virtual bool onNotify(const float &zeEvent);

protected:
    Vector3 goToThatPoint;
    bool isMovingTowardsThatPos;
};