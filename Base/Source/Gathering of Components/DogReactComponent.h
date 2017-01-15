#pragma once

#include "../GenericECS/GenericComponent.h"

class StateMachineComponent;
class DogReactComponent : public GenericComponent
{
public:
    DogReactComponent();
    virtual ~DogReactComponent();

    virtual bool onNotify(const std::string &zeEvent);

    static const unsigned char ID_ = 9;
protected:
    std::string receivedMessage;
    StateMachineComponent *FSM_;    // Need to know what state the dog is in.
};