#pragma once

#include "StateComponent.h"
#include "Vector3.h"

class Devil_SearchState : public StateComponent
{
public:
	Devil_SearchState();
	virtual ~Devil_SearchState();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Exit();

	const static unsigned char ID_ = 0;

	virtual bool onNotify(const std::string &zeEvent);

private:
	float timer;
	
	Vector3 searchVel, enemyLastSeen;
	GenericComponent *zeVictim;
	
	bool showReplying;
};