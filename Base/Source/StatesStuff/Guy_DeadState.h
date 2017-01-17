#pragma once

#include "StateComponent.h"
#include "Vector3.h"

class Guy_DeadState : public StateComponent
{
public:
	Guy_DeadState();
	virtual ~Guy_DeadState();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Exit();

	const static unsigned char ID_ = 4;
};