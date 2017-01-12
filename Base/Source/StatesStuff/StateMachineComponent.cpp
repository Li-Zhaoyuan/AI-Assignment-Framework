#include "StateMachineComponent.h"
#include "../Classes/GameEntity.h"

ID_Component StateMachineComponent::ID_(1);

StateMachineComponent::StateMachineComponent()
{
    Init();
}

StateMachineComponent::~StateMachineComponent()
{
    for (auto it : allRegisteredStates)
        if (it)
            delete it;
    allRegisteredStates.clear();
    HistoryOfStates.clear();
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
    HistoryOfStates.clear();
    for (std::vector<StateComponent*>::iterator it = allRegisteredStates.begin(), end = allRegisteredStates.end(); it != end; ++it)
    {
        if (*it)
            (*it)->Exit();
    }
    HistoryOfStates.push_back(allRegisteredStates[0]);
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
        zeStates.setFSM(*this);
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

void StateMachineComponent::switchState(const size_t &zeID)
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
            HistoryOfStates.back()->Exit();
            HistoryOfStates.push_back(*it);
            break;
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

StateComponent &StateMachineComponent::getCurrentState()
{
    return *HistoryOfStates.back();
}

bool StateMachineComponent::onNotify(GenericComponent &zeEvent)
{
	HistoryOfStates.back()->onNotify(zeEvent);
	return true;
}

bool StateMachineComponent::onNotify(const std::string &zeEvent)
{
    return HistoryOfStates.back()->onNotify(zeEvent);
}

bool StateMachineComponent::onNotify(const int &zeEvent)
{
    return HistoryOfStates.back()->onNotify(zeEvent);
}

bool StateMachineComponent::onNotify(const float &zeEvent)
{
    return HistoryOfStates.back()->onNotify(zeEvent);
}