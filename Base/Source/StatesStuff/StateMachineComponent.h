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
    void switchState(const size_t &zeID);
    void switchState(const std::string &zeName);
    bool transitToPreviousState();

    static ID_Component ID_;
    StateComponent &getSpecificStates(const size_t &zeNum);
    StateComponent &getSpecificStates(const std::string &zeName);
    StateComponent &getCurrentState();

    // All OnNotify calls will go straight to the current state onNotify
	virtual bool onNotify(GenericComponent &zeEvent);
    // All OnNotify calls will go straight to the current state onNotify
    virtual bool onNotify(const std::string &zeEvent);
    // All OnNotify calls will go straight to the current state onNotify
    virtual bool onNotify(const int &zeEvent);
    // All OnNotify calls will go straight to the current state onNotify
    virtual bool onNotify(const float &zeEvent);

protected:
    std::vector<StateComponent*> allRegisteredStates, HistoryOfStates;
};

#endif