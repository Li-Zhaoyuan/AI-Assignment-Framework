#pragma once

#include "../GenericECS/GenericComponent.h"
#include <vector>

class ZombieAnimComp : public GenericComponent
{
public:
    ZombieAnimComp();
    virtual ~ZombieAnimComp();

    virtual void Update(double dt);

    static const unsigned char ID_ = 3;

private:
    std::vector<GenericComponent*> allAnimations;
};