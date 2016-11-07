#pragma once

#include "../GenericECS/GenericComponent.h"

class SpeedComponent : public GenericComponent
{
public:
    SpeedComponent();
    virtual ~SpeedComponent();

    virtual void Init();

    virtual bool onNotify(const float &zeEvent);

    static const unsigned char ID_ = 5;

protected:
    float speed_;
};