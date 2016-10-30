#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "MyMeshComponent.h"

class SpriteComponent : public MyMeshComponent
{
public:
    //Don't forget about the ability to go backwards!
    SpriteComponent();
    SpriteComponent(const std::string &zeName, GenericEntity *zeOwner, const size_t &zeRow, const size_t &zeCol);
    virtual ~SpriteComponent();

    virtual void Render();

protected:

};

#endif