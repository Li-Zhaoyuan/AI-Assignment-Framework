#include "MessageSystem.h"

void MessageSystem::Update(double dt)
{

}

bool MessageSystem::onNotify(const std::string &zeEvent)
{
    SendMessage.push_back(zeEvent);
    return true;
}