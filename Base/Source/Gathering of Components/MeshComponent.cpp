#include "MeshComponent.h"
#include "../Systems/ComponentSystem.h"

ID_Component MeshComponent::g_CompID_(0);

MeshComponent::MeshComponent()
{
    Init();
}

MeshComponent::MeshComponent(const unsigned short &zeNum)
{
    meshID_ = zeNum;
}

MeshComponent::~MeshComponent()
{

}


//void MeshComponent::Render()
//{
//    
//}

bool MeshComponent::onNotify(const std::string &zeEvent)
{
    if (zeEvent.size() > 0)
    {
        meshName_ = zeEvent;
        return true;
    }
    return false;
}

bool MeshComponent::onNotify(const int &zeEvent)
{
    if (zeEvent >= 0)
    {
        meshID_ = zeEvent;
        return true;
    }
    return false;
}

void MeshComponent::Init()
{
    meshID_ = 0;
    meshName_ = "";
}

unsigned short &MeshComponent::getMeshID()
{
    return meshID_;
}