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

protected:
    Vector3 *boundaryOfThePlace;
    Vector3 goToThatPoint;
    bool isMovingTowardsThatPos;
    bool hasChangedName;
};