#pragma once

#include "StateComponent.h"
#include "Vector3.h"

class Guy_PatrolState : public StateComponent
{
public:
	Guy_PatrolState();
	virtual ~Guy_PatrolState();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Exit();

	const static unsigned char ID_ = 0;

private:
	float timer;
	float patrolAngle;
	float rangeToStartPatrolling;
	float radiusToPatrolPoint;
	bool hasNameChange;

	Vector3 searchVel, pointToPatrol, originToPatrolPos;

};