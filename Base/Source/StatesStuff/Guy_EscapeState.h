#pragma once

#include "StateComponent.h"
#include "Vector3.h"

class Guy_EscapeState : public StateComponent
{
public:
	Guy_EscapeState();
	virtual ~Guy_EscapeState();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Exit();

	const static unsigned char ID_ = 1;

private:
	float timer;
	

};