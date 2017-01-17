#pragma once

#include "StateComponent.h"
#include "Vector3.h"

class Devil_DeadState : public StateComponent
{
public:
	Devil_DeadState();
	virtual ~Devil_DeadState();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Exit();

	const static unsigned char ID_ = 4;
};