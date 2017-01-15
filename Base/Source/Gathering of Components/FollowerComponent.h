#pragma once

#include "../GenericECS/GenericComponent.h"
#include "../Classes/GameEntity.h"

class FollowerComponent : public GenericComponent
{
public:
    FollowerComponent();
    virtual ~FollowerComponent();

    // This is to add the leader so that it can recognise the leader but can only be used once.
    virtual bool onNotify(GenericEntity &zeEvent);

    GameEntity *getTheLeader();

    static const unsigned char ID_ = 10;

private:
    GameEntity *theLeader;
};