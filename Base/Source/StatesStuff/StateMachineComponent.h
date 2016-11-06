#ifndef STATE_MACHINE_COMPONENT_H
#define STATE_MACHINE_COMPONENT_H

#include "../GenericECS/GenericComponent.h"
#include "../Gathering of Components/ID_Component.h"
#include "StateComponent.h"
#include <vector>

class StateComponent;

class StateMachineComponent : public GenericComponent
{
public:
    StateMachineComponent();
    virtual ~StateMachineComponent();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Exit();

    void addStates(StateComponent &zeStates, const size_t &zeID);
    void switchStates(const size_t &zeID);
    void switchState(const std::string &zeName);
    bool transitToPreviousState();

    static ID_Component ID_;
    StateComponent &getSpecificStates(const size_t &zeNum);
    StateComponent &getSpecificStates(const std::string &zeName);

protected:
    std::vector<StateComponent*> allRegisteredStates, HistoryOfStates;
};

#endif