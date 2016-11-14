#include "IdleState.h"
#include "../Misc/GlobalFunctions.h"

IdleState::IdleState()
{
    Init();
}

IdleState::~IdleState()
{

}

void IdleState::Init()
{
    name_ = "IDLE";
    changedName = false;
    originalOwnerName = "";
}

void IdleState::Update(double dt)
{
    switch (changedName)
    {
    case false:
    {
        std::string newName = owner_of_component->getName();
        originalOwnerName = newName;
        newName.append(name_);
        owner_of_component->setName(newName);
        changedName = true;
    }
        break;
    default:
        break;
    }
}

void IdleState::Exit()
{
    changedName = false;
    owner_of_component->setName(originalOwnerName);
}

bool IdleState::onNotify(const std::string &zeEvent)
{
    //if (checkWhetherTheWordInThatString("GO", zeEvent))
    //{
    //    FSM_->switchState(2);
    //    FSM_->
    //    return true;
    //}
    return false;
}