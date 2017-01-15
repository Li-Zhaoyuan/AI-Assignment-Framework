#pragma once

#include "../GenericECS/GenericComponent.h"

class FollowerComponent : public GenericComponent
{
public:
    FollowerComponent();
    virtual ~FollowerComponent();

    static const unsigned char ID_ = 10;
};