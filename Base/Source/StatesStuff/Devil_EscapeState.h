#pragma once

#include "StateComponent.h"
#include "Vector3.h"

class Devil_EscapeState : public StateComponent
{
public:
	Devil_EscapeState();
	virtual ~Devil_EscapeState();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Exit();

	const static unsigned char ID_ = 2;

private:
	float timer;


};