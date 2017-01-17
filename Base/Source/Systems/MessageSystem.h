#pragma once

#include "../GenericECS/GenericSystem.h"
#include "../Classes/singletontemplate.h"
#include <list>
#include <vector>

class MessageSystem : public GenericSystem, public SingletonTemplate<MessageSystem>
{
    friend SingletonTemplate<MessageSystem>;
public:
    //Init does nothing!
    virtual void Init();

    // Removes A message every time it is called (or frame)
    virtual void Update(double dt);

    //clear all the message
    virtual void Exit();
    //Entities that want to send message to the system use this function!
    virtual bool onNotify(const std::string &zeEvent);
    // Get the first message that is being send to this system. new message appears every frame assuming Update is being called. The string will be empty when there is no more message
    std::string getMessage();
    std::vector<std::string> StoreMessage;

private:
    std::list<std::string> SendingMessage;
    MessageSystem() {}
    virtual ~MessageSystem() {}
};