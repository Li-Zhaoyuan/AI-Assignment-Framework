#pragma once

#include "StateComponent.h"
#include "Vector3.h"

class Guy_AttackState : public StateComponent
{
public:
	Guy_AttackState();
	virtual ~Guy_AttackState();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Exit();

	const static unsigned char ID_ = 3;


private:
	float timer;

};