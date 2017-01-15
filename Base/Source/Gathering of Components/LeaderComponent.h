#pragma once

#include "../GenericECS/GenericComponent.h"
#include "../Classes/GameEntity.h"
#include <unordered_map>

class LeaderComponent : public GenericComponent
{
public:
    LeaderComponent();
    virtual ~LeaderComponent();

    // This is just for adding the all the followers into it's map using their name as the key.
    virtual bool onNotify(GenericEntity &zeEvent);
    GameEntity *getFollower(const std::string &zeName);

    static const unsigned char ID_ = 11;

private:
    // using unordered map so it can access the string faster.
    std::unordered_map<std::string, GameEntity*> allOfItsFollowers;
};