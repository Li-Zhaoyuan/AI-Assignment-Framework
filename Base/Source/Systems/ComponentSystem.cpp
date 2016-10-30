#include "ComponentSystem.h"

void ComponentSystem::Init()
{

}

void ComponentSystem::Update(double dt)
{

}

void ComponentSystem::Exit()
{
    for (auto it : bunchOfComponents)
    {
        delete it.second;
        it.second = nullptr;
    }
    bunchOfComponents.clear();
}

GenericComponent &ComponentSystem::gettingComponent(const size_t &zeID)
{
    return *bunchOfComponents[zeID];
}

bool ComponentSystem::addingComponents(GenericComponent *zeNewComp)
{
    //if (bunchOfComponents.find(zeNewComp->getID()) == bunchOfComponents.end())
    //{   
    //    bunchOfComponents.insert(std::pair<size_t, GenericComponent*>(zeNewComp->getID(), zeNewComp));
    //    return true;
    //}
    return false;
}