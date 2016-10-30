#include "GenericComponent.h"


GenericComponent::GenericComponent()
{
    GenericComponent("", nullptr);
}

GenericComponent::GenericComponent(const std::string &zeName)
{
    GenericComponent(zeName, nullptr);
}

GenericComponent::GenericComponent(const std::string &zeName, GenericEntity *zeOwner)
{
    setName(zeName);
    owner_of_component = zeOwner;
}

GenericComponent::~GenericComponent()
{
    Exit();
}

void GenericComponent::setName(const std::string zeName) 
{ 
    name_ = zeName; 
}

void GenericComponent::setEntityOwner(GenericEntity *zeOwner) 
{ 
    owner_of_component = zeOwner; 
}


std::string GenericComponent::getName()
{
    return name_;
}

GenericEntity &GenericComponent::getOwner()
{
    return *owner_of_component;
}

void GenericComponent::Init()
{

}

void GenericComponent::Update(double dt)
{

}

void GenericComponent::Exit()
{
    owner_of_component = nullptr;
}
