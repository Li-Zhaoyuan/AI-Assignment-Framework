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
    //if (!HistoryOfStates.empty())
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
    while (allRegisteredStates.size() <= zeID)
    {
        allRegisteredStates.resize(allRegisteredStates.size() * 2, nullptr);
    }
    if (!allRegisteredStates[zeID])
    {
        allRegisteredStates[zeID] = &zeStates;
        if (HistoryOfStates.empty())
            HistoryOfStates.push_back(&zeStates);
        zeStates.setEntityOwner(owner_of_component);
    }
}

bool StateMachineComponent::transitToPreviousState()
{
    if (HistoryOfStates.size() > 1) {
        HistoryOfStates.back()->Exit();
        HistoryOfStates.pop_back();
        return true;
    }
    return false;
}

void StateMachineComponent::switchStates(const size_t &zeID)
{
    HistoryOfStates.back()->Exit();
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

StateComponent &StateMachineComponent::getSpecificStates(const size_t &zeNum)
{
    return *allRegisteredStates[zeNum];
}

StateComponent &StateMachineComponent::getSpecificStates(const std::string &zeName)
{
    std::vector<StateComponent*>::iterator it = allRegisteredStates.begin();
    for (std::vector<StateComponent*>::iterator it = allRegisteredStates.begin(), end = allRegisteredStates.end(); it != end; ++it)
    {
        if ((*it)->getName() == zeName)
        {
            break;
        }
    }
    return **it;
}