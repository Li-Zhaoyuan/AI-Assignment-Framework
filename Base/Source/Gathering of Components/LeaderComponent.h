#pragma once

#include "../GenericECS/GenericComponent.h"
#include "../Classes/GameEntity.h"
#include <unordered_map>

class LeaderComponent : public GenericComponent
{
public:
    LeaderComponent();
    virtual ~LeaderComponent();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Exit();

    virtual bool onNotify(GenericEntity &zeEvent);

    static const unsigned char ID_ = 11;

private:

    bool changeLeaderName;  // Need to check whether it has change any name
    std::string originalName;   // Able to retain the entity original name
};