#pragma once

#include "../GenericECS/GenericComponent.h"
class StateMachineComponent;

class ManReactComponent : public GenericComponent
{
public:
    ManReactComponent();
    virtual ~ManReactComponent();

    // Message System will send the message to the component through onNotify(string). It will decipher whether the message is worthy or not from here
    virtual bool onNotify(const std::string &zeEvent);
    static const unsigned char ID_ = 9; // just it's ID for entity to keep in check

private:
    std::string receivedMessage;
    StateMachineComponent *FSM_;
};