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

	void setWayPoints();
private:
	bool isAtWayPoint;
	int currPoint, nextPoint;
	Vector3 wayPoints[4];
	Vector3 pointToPatrol, vel;

};