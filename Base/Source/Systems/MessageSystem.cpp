#include "MessageSystem.h"

void MessageSystem::Init()
{

}

void MessageSystem::Update(double dt)
{
    if (!SendingMessage.empty())
    {
        StoreMessage.push_back(SendingMessage.front());
        SendingMessage.pop_front();
    }
}

void MessageSystem::Exit()
{
    SendingMessage.clear();
    StoreMessage.clear();
}

bool MessageSystem::onNotify(const std::string &zeEvent)
{
    SendingMessage.push_back(zeEvent);
    return true;
}

std::string MessageSystem::getMessage()
{
    if (SendingMessage.empty())
        return  "";
    return SendingMessage.front();
}