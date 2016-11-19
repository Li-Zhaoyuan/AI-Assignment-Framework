#pragma once

#include "StateComponent.h"
#include "Vector3.h"

class Guy_StunState : public StateComponent
{
public:
	Guy_StunState();
	virtual ~Guy_StunState();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Exit();

	const static unsigned char ID_ = 2;

	
private:
	float timer;

};