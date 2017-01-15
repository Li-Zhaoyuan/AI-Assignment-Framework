#include "LeaderComponent.h"

LeaderComponent::LeaderComponent()
{
    name_ = "Leader Component";
}

LeaderComponent::~LeaderComponent()
{

}

bool LeaderComponent::onNotify(GenericEntity &zeEvent)
{
    //allOfItsFollowers.push_back(dynamic_cast<GameEntity*>(&zeEvent));
    allOfItsFollowers.insert(std::pair<std::string, GameEntity*>(zeEvent.getName(), dynamic_cast<GameEntity*>(&zeEvent)));
    return true;
}

GameEntity *LeaderComponent::getFollower(const std::string &zeName)
{
    return allOfItsFollowers[zeName];
}