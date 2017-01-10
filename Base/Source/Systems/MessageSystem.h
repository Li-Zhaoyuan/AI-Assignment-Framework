#pragma once

#include "../GenericECS/GenericSystem.h"
#include "../Classes/singletontemplate.h"
#include <map>
#include <vector>

class MessageSystem : public GenericSystem, public SingletonTemplate<MessageSystem>
{
public:
    virtual void Update(double dt);
    virtual bool onNotify(const std::string &zeEvent);

    std::vector<std::string> SendMessage, StoreMessage;
};