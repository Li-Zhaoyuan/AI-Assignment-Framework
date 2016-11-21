#pragma once

#include "../GenericECS/GenericComponent.h"
#include <vector>

class GuyAnimComp : public GenericComponent
{
public:
	GuyAnimComp();
	virtual ~GuyAnimComp();

	virtual void Update(double dt);

	static const unsigned char ID_ = 3;

private:
	std::vector<GenericComponent*> allAnimations;
};