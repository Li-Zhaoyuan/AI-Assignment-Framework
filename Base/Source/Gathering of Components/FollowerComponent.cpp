#include "FollowerComponent.h"

FollowerComponent::FollowerComponent()
{
    name_ = "Follower Component";
    theLeader = nullptr;
}

FollowerComponent::~FollowerComponent()
{

}

bool FollowerComponent::onNotify(GenericEntity &zeEvent)
{
    if (!theLeader)
    {
        theLeader = dynamic_cast<GameEntity*>(&zeEvent);
        return true;
    }
    return false;
}

GameEntity *FollowerComponent::getTheLeader()
{
    return theLeader;
}