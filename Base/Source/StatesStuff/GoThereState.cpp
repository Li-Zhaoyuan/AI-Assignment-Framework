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
    changedName = false;
    originalOwnerName = "";
    name_ = "GOING";
    updatedSpeed = false;
}

void GoThereState::Update(double dt)
{
    switch (changedName)
    {
    case false:
    {
        originalOwnerName = owner_of_component->getName();
        std::string zeName = originalOwnerName;
        zeName.append(name_);
        owner_of_component->setName(zeName);
        changedName = true;
    }
        break;
    default:
        break;
    }

    GameEntity *zeOwner = dynamic_cast<GameEntity*>(owner_of_component);
    PhysicsComponent *zeOwnerPos = dynamic_cast<PhysicsComponent*>(&zeOwner->getComponent(PhysicsComponent::g_ID_));
    switch (updatedSpeed)
    {
    case false:
    {
        zeOwnerPos->setVel((goThatPos - zeOwnerPos->getPos()).Normalized() * 20);
        updatedSpeed = true;
    }
        break;
    default:
        if ((zeOwnerPos->getPos() - goThatPos).LengthSquared() < 4.f)
        {
            FSM_->switchState(0);
            zeOwnerPos->setVel(Vector3(0, 0, 0));
        }
        break;
    }
}

void GoThereState::Exit()
{
    changedName = false;
    owner_of_component->setName(originalOwnerName);
    updatedSpeed = false;
    GameEntity *zeOwner = dynamic_cast<GameEntity*>(owner_of_component);
    PhysicsComponent *zeOwnerPos = dynamic_cast<PhysicsComponent*>(&zeOwner->getComponent(PhysicsComponent::g_ID_));
    zeOwnerPos->setVel(Vector3(0, 0, 0));
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
        FSM_->switchState(0);
    }
    return false;
}