#pragma once

#include "../GenericECS/GenericComponent.h"
#include "../Classes/GameEntity.h"
#include <unordered_map>

class LeaderComponent : public GenericComponent
{
public:
    LeaderComponent();
    virtual ~LeaderComponent();

    static const unsigned char ID_ = 11;
};