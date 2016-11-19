#pragma once

#include "StateComponent.h"
#include "Vector3.h"

class Devil_HealState : public StateComponent
{
public:
	Devil_HealState();
	virtual ~Devil_HealState();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Exit();

	const static unsigned char ID_ = 3;

private:
	float timer;


};