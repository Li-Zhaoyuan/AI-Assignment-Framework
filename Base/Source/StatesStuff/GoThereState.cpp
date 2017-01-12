#include "GoThereState.h"
#include "../Misc/GlobalFunctions.h"
#include "../Classes/GameEntity.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include <exception>
#include <iostream>
#include "../Gathering of Components/SpeedComponent.h"

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
    SpeedComponent *zeSpeed = dynamic_cast<SpeedComponent*>(&zeOwner->getComponent(SpeedComponent::ID_));
    zeOwnerPos->setVel((goThatPos - zeOwnerPos->getPos()).Normalized() * zeSpeed->getSpeed());
    switch (updatedSpeed)
    {
    case false:
    {
        //zeOwnerPos->setVel((goThatPos - zeOwnerPos->getPos()).Normalized() * zeSpeed->getSpeed());
        updatedSpeed = true;
    }
        break;
    default:
        Vector3 DirToDest = zeOwnerPos->getPos() - goThatPos;   // Getting the direction from own position to the destination
        if (DirToDest.LengthSquared() < 4.f)    // Check to see if it reached it's destination. 4.f will be an offset radius
        {
            FSM_->switchState(0);
            zeOwnerPos->setVel(Vector3(0, 0, 0));
            break;
        }
        //DirToDest.Normalized();
        //if (DirToDest.Dot(zeOwnerPos->getVel().Normalize()) <= 0)  // Check whether is it going in the right direction. If not, recalculate the velocity.
        //    updatedSpeed = false;
        break;
    }
}

void GoThereState::Exit()
{
    changedName = false;
    if (originalOwnerName != "")
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
            anotherStr = anotherStr.substr(posOfComma+1);
            posOfComma = anotherStr.find(',');
            y = stof(anotherStr.substr(0, posOfComma));
            anotherStr = anotherStr.substr(posOfComma+1);
            z = stof(anotherStr);
            GameEntity *zeOwner = dynamic_cast<GameEntity*>(owner_of_component);
            PhysicsComponent *zeOwnerPos = dynamic_cast<PhysicsComponent*>(&zeOwner->getComponent(PhysicsComponent::g_ID_));
            x = Math::Clamp(x, -zeOwnerPos->getBoundary().x + zeOwnerPos->getSize().x, zeOwnerPos->getBoundary().x - zeOwnerPos->getSize().x);
            y = Math::Clamp(y, -zeOwnerPos->getBoundary().y + zeOwnerPos->getSize().y, zeOwnerPos->getBoundary().y - zeOwnerPos->getSize().y);
            goThatPos.Set(x, y, z);
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