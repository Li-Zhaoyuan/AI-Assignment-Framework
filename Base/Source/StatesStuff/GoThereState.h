#pragma once

#include "StateComponent.h"
#include "Vector3.h"

class GoThereState : public StateComponent
{
public:
    GoThereState();
    virtual ~GoThereState();

    static const unsigned char ID_ = 1;

    virtual void Init();
    virtual void Update(double dt);
    virtual void Exit();
    virtual bool onNotify(const std::string &zeEvent);

private:
    Vector3 goThatPos;
};