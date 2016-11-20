#pragma once

#include "../GenericECS/GenericComponent.h"
#include <vector>

class ZombieAnimComp : public GenericComponent
{
public:
    ZombieAnimComp();
    virtual ~ZombieAnimComp();

    virtual void Update(double dt);

private:
    static std::vector<GenericComponent*> allAnimations;
};