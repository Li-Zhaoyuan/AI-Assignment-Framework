#pragma once

#include "../GenericECS/GenericComponent.h"

class LeaderComponent : public GenericComponent
{
public:
    LeaderComponent();
    virtual ~LeaderComponent();

    static const unsigned char ID_ = 10;
};