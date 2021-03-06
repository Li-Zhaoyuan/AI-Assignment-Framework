//Devil_AttackState
#pragma once

#include "StateComponent.h"
#include "Vector3.h"

class Devil_AttackState : public StateComponent
{
public:
	Devil_AttackState();
	virtual ~Devil_AttackState();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Exit();

	const static unsigned char ID_ = 1;
private:
	float timer;
	int chance;
	Vector3 searchVel;
};