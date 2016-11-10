#pragma once

#include "StateComponent.h"

class IdleState : public StateComponent
{
public:
    IdleState();
    virtual ~IdleState();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Exit();

    const static unsigned char ID_ = 0;

    virtual bool onNotify(const std::string &zeEvent);

private:
    bool hasNameChange;
    std::string originalOwnerName;
};