#pragma once

#include "../GenericECS/GenericSystem.h"
#include "../Classes/singletontemplate.h"
#include <list>
#include <vector>

class MessageSystem : public GenericSystem, public SingletonTemplate<MessageSystem>
{
public:
    virtual void Init();
    virtual void Update(double dt);
    virtual void Exit();

    virtual bool onNotify(const std::string &zeEvent);

    std::string getMessage();
    std::vector<std::string> StoreMessage;

private:
    std::list<std::string> SendingMessage;
};