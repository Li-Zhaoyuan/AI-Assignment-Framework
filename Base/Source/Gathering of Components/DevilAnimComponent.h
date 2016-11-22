#pragma once

#include "../GenericECS/GenericComponent.h"
#include <vector>

class DevilAnimComp : public GenericComponent
{
public:
	DevilAnimComp();
	virtual ~DevilAnimComp();

	virtual void Update(double dt);

	static const unsigned char ID_ = 3;

private:
	std::vector<GenericComponent*> allAnimations;
};