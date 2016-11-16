#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "../Gathering of Components/MyMeshComponent.h"

class SpriteComponent : public MyMeshComponent
{
public:
    //Don't forget about the ability to go backwards!
    SpriteComponent();
    SpriteComponent(const std::string &zeName, const size_t &zeRow, const size_t &zeCol);
    virtual ~SpriteComponent();

    virtual void Render();

    virtual bool onNotify(GenericComponent &zeEvent);
    int m_row;
    int m_col;
    int m_currentFrame;

    bool doReversal;
    bool oppositeWay;
    bool unlimitedTimes;

protected:
    GenericComponent *zeAnimTime;
};

#endif