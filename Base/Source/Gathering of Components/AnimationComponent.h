#pragma once

#include "../GenericECS/GenericComponent.h"

class AnimationComponent : public GenericComponent
{
public:
    AnimationComponent() { m_currentTime = 0; };
    virtual ~AnimationComponent() {};

    virtual void Update(double dt) { m_currentTime += (float)(dt); }

    void Set(int startFrame, int endFrame, int repeat, float time, bool active)
    {
        this->startFrame = startFrame;
        this->endFrame = endFrame;
        this->repeatCount = repeat;
        this->animTime = time;
        this->animActive = active;
    }

    int startFrame;
    int endFrame;
    int repeatCount;
    float animTime, m_currentTime;
    bool animActive;
    const static unsigned char ID_ = 3;
};