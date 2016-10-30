#ifndef COMPONENT_SYSTEM_H
#define COMPONENT_SYSTEM_H

#include "../GenericECS/GenericSystem.h"
#include "../Classes/singletontemplate.h"
#include "../GenericECS/GenericComponent.h"
#include <map>
class GenericComponent;

typedef std::map<size_t, GenericComponent*> uGCmap;

class ComponentSystem : public GenericSystem, public SingletonTemplate<ComponentSystem>
{
public:
    virtual void Init();
    virtual void Update(double dt);
    virtual void Exit();

    GenericComponent &gettingComponent(const size_t &zeID);
    bool addingComponents(GenericComponent *zeNewComp);

private:
    std::map<size_t, GenericComponent*> bunchOfComponents;
};

#endif