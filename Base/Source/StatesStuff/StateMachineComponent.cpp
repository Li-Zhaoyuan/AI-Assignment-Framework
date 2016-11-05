#include "StateMachineComponent.h"
#include "../Classes/GameEntity.h"

ID_Component StateMachineComponent::ID_(1);

StateMachineComponent::StateMachineComponent()
{
    Init();
}

StateMachineComponent::~StateMachineComponent()
{
    Exit();
}

void StateMachineComponent::Init()
{
    allRegisteredStates.resize(2, nullptr);
}

void StateMachineComponent::Update(double dt)
{
    if (!HistoryOfStates.empty())
        HistoryOfStates.back()->Update(dt);
}

void StateMachineComponent::Exit()
{
    for (auto it : allRegisteredStates)
        delete it;
    allRegisteredStates.clear();
    HistoryOfStates.clear();
}

void StateMachineComponent::addStates(StateComponent &zeStates, const size_t &zeID)
{
    allRegisteredStates.push_back(&zeStates);
    if (HistoryOfStates.empty())
        HistoryOfStates.push_back(&zeStates);
}

bool StateMachineComponent::transitToPreviousState()
{
    if (HistoryOfStates.size() > 1) {
        HistoryOfStates.pop_back();
        return true;
    }
    return false;
}

void StateMachineComponent::switchStates(const size_t &zeID)
{
    HistoryOfStates.push_back(allRegisteredStates[zeID]);
}

void StateMachineComponent::switchState(const std::string &zeName)
{
    for (std::vector<StateComponent*>::iterator it = allRegisteredStates.begin(), end = allRegisteredStates.end(); it != end; ++it)
    {
        if ((*it)->getName() == zeName)
        {
            HistoryOfStates.push_back(*it);
        }
    }
}