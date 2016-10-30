#ifndef MY_MESH_COMPONENT_H
#define MY_MESH_COMPONENT_H

#include "../GenericECS/GenericComponent.h"
#include "../Classes/Material.h"

class MyMeshComponent : public GenericComponent
{
public:
    static const size_t MAX_TEXTURES = 2;
    enum DRAW_MODE {
        DRAW_TRIANGLES,
        DRAW_TRIANGLE_STRIP,
        DRAW_LINES,
        DRAW_MODE_LAST,
    };
    MyMeshComponent();
    MyMeshComponent(const std::string &zeName, GenericEntity *zeOwner);
    virtual ~MyMeshComponent();

    virtual void Render();
    void Render(unsigned offset, unsigned count);

    const std::string name;
    DRAW_MODE mode;
    unsigned vertexBuffer;
    unsigned indexBuffer;
    unsigned indexSize;

    Material material;
    unsigned textureID;
    //Week 4 Texture Array
    unsigned textureArray[MAX_TEXTURES];
};

#endif