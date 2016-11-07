#ifndef STATE_COMPONENT_H
#define STATE_COMPONENT_H

#include "../GenericECS/GenericComponent.h"
#include "../Gathering of Components/ID_Component.h"
#include "StateMachineComponent.h"

class StateMachineComponent;

class StateComponent : public GenericComponent
{
public:
    virtual ~StateComponent() { FSM_ = nullptr; };
protected:
    StateMachineComponent *FSM_;
    StateComponent() { FSM_ = nullptr; };
};

#endif