#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include "../GenericECS/GenericComponent.h"
#include "ID_Component.h"

class MeshComponent : public GenericComponent
{
public:
    MeshComponent();
    MeshComponent(const unsigned short &zeNum);
    virtual ~MeshComponent();

    virtual void Init();

    virtual bool onNotify(const std::string &zeEvent);
    virtual bool onNotify(const int &zeEvent);
    //void Render();

    unsigned short &getMeshID();

    static ID_Component g_CompID_;

protected:
    unsigned short meshID_;
    std::string meshName_;
};

#endif