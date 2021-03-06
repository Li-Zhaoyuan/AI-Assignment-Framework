#ifndef STATE_COMPONENT_H
#define STATE_COMPONENT_H

#include "../GenericECS/GenericComponent.h"
#include "../Gathering of Components/ID_Component.h"
#include "StateMachineComponent.h"

class StateMachineComponent;

class StateComponent : public GenericComponent
{
public:
    virtual ~StateComponent() { FSM_ = nullptr; changedName = false; originalOwnerName = ""; influenceRadius = 0; };

    void setFSM(StateMachineComponent &zeFSM) { FSM_ = &zeFSM; }
	std::string getOriginalOwnerName() { return originalOwnerName; }
protected:
    StateMachineComponent *FSM_;
    StateComponent() { reactingToMessage = false; changedName = false; FSM_ = nullptr; originalOwnerName = ""; influenceRadius = 0; };
    std::string originalOwnerName;
    bool changedName, reactingToMessage;
    float influenceRadius;
};

#endif