#pragma once

#include "../GenericECS/GenericComponent.h"

class StateMachineComponent;
class AllyEnemyComponent;
class DogReactComponent : public GenericComponent
{
public:
    DogReactComponent();
    virtual ~DogReactComponent();

    // This is for the dog to react to messages accordingly
    virtual bool onNotify(const std::string &zeEvent);
    // This is to toggle certain event that only Sek Heng can use!
    virtual bool onNotify(const int &zeEvent);

    static const unsigned char ID_ = 9;
protected:
    std::string receivedMessage;
    StateMachineComponent *FSM_;    // Need to know what state the dog is in.
    AllyEnemyComponent *listOfAllyEnemy;    // Need to know check through it's ally list
    bool HasReactedToMessage;
};