#pragma once

#include "StateComponent.h"

class Devil_SearchState : public StateComponent
{
public:
	Devil_SearchState();
	virtual ~Devil_SearchState();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Exit();

	const static unsigned char ID_ = 0;

};