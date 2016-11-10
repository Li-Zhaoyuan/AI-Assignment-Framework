#include "GoThereState.h"
#include "../Misc/GlobalFunctions.h"
#include "../Classes/GameEntity.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include <exception>
#include <iostream>

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

    GameEntity *zeOwner = dynamic_cast<GameEntity*>(owner_of_component);
    PhysicsComponent *zeOwnerPos = dynamic_cast<PhysicsComponent*>(&zeOwner->getComponent(PhysicsComponent::g_ID_));
    if ((zeOwnerPos->getPos() - goThatPos).LengthSquared() < 4.f)
        FSM_->switchState(0);
}

void GoThereState::Exit()
{
    updateName = false;
    owner_of_component->setName(originalOwnerName);
}

bool GoThereState::onNotify(const std::string &zeEvent)
{
    try {
        if (checkWhetherTheWordInThatString("GO", zeEvent))
        {
            std::string anotherStr = zeEvent.substr(3);
            float x, y, z;
            size_t posOfComma = anotherStr.find(',');
            x = stof(anotherStr.substr(0, posOfComma));
            anotherStr = anotherStr.substr(posOfComma);
            y = stof(anotherStr.substr(0, posOfComma));
            anotherStr = anotherStr.substr(posOfComma);
            z = stof(anotherStr);
            return true;
        }
    }
    catch (std::exception ex)
    {
        std::cout << ex.what() << std::endl;
    }
    return false;
}