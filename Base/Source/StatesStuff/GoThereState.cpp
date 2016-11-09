#include "GoThereState.h"
#include "../Misc/GlobalFunctions.h"

GoThereState::GoThereState()
{
    Init();
}

GoThereState::~GoThereState()
{

}

void GoThereState::Init()
{
    updateName = false;
    originalOwnerName = "";
    name_ = "GOING";
}

void GoThereState::Update(double dt)
{
    switch (updateName)
    {
    case false:
    {
        originalOwnerName = owner_of_component->getName();
        std::string zeName = originalOwnerName;
        zeName.append(name_);
        owner_of_component->setName(zeName);
        updateName = true;
    }
        break;
    default:
        break;
    }
}

void GoThereState::Exit()
{
    updateName = false;
    owner_of_component->setName(originalOwnerName);
}

bool GoThereState::onNotify(const std::string &zeEvent)
{
    
    return false;
}