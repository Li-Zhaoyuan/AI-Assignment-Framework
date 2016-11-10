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

    void setInfluenceRadius(const float &zeRadius);

protected:
    Vector3 goToThatPoint;
    bool isMovingTowardsThatPos;
    float influenceRadius;
};