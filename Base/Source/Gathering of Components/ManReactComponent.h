#pragma once

#include "../GenericECS/GenericComponent.h"
class StateMachineComponent;
class AllyEnemyComponent;
class ManReactComponent : public GenericComponent
{
public:
    ManReactComponent();
    virtual ~ManReactComponent();

    // Message System will send the message to the component through onNotify(string). It will decipher whether the message is worthy or not from here
    virtual bool onNotify(const std::string &zeEvent);
    static const unsigned char ID_ = 9; // just it's ID for entity to keep in check
    // The values passed in will affect the chance that the Guy will react to the less important message. For example, passing in 2 will means Guy's react chances is 1 in 2.
    virtual bool onNotify(const int &zeEvent);

private:
    std::string receivedMessage;
    StateMachineComponent *FSM_;
    AllyEnemyComponent *listOfAllyEnemy;    // Need to know check through it's ally list
    int chanceToReact;
    bool HasReactToMessage;
};