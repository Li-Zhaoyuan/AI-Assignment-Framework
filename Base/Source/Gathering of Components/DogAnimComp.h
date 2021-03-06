#pragma once

#include "../GenericECS/GenericComponent.h"
#include <vector>

class DogAnimComp : public GenericComponent
{
public:
    DogAnimComp();
    virtual ~DogAnimComp();

    virtual void Update(double dt);

    static const unsigned char ID_ = 3;

private:
    std::vector<GenericComponent*> allAnimations;
};