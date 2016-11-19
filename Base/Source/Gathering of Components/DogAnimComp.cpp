#include "DogAnimComp.h"
#include "PhysicsComponent.h"
#include "../Classes/GameEntity.h"
#include "AnimationComponent.h"
#include "../Misc/DetectMemoryLeak.h"

std::vector<GenericComponent*> DogAnimComp::allAnimations;

DogAnimComp::DogAnimComp()
{
    if (allAnimations.empty())
    {
        // Right
        AnimationComponent *Animation1 = new AnimationComponent();
        Animation1->Set(4, 7, 10000, 0.5f, true);
        Animation1->unlimitedTimes = true;
        Animation1->setName("RIGHT");
        allAnimations.push_back(Animation1);

        //Left
        Animation1 = new AnimationComponent();
        Animation1->Set(12, 15, 10000, 0.5f, true);
        Animation1->unlimitedTimes = true;
        allAnimations.push_back(Animation1);
        Animation1->setName("LEFT");

        //Up
        Animation1 = new AnimationComponent();
        Animation1->Set(8, 11, 1000, 0.5f, true);
        Animation1->unlimitedTimes = true;
        allAnimations.push_back(Animation1);
        Animation1->setName("UP");

        //Down
        Animation1 = new AnimationComponent;
        Animation1->Set(0, 3, 10000, 0.5f, true);
        Animation1->unlimitedTimes = true;
        allAnimations.push_back(Animation1);
        Animation1->setName("DOWN");
    }
    currAnimation = allAnimations[0];
    hasThePointerBeenActivated = false;
}

DogAnimComp::~DogAnimComp()
{
    GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
    zeGo->eraseComponent(AnimationComponent::ID_);
    if (!allAnimations.empty())
    {
        for (std::vector<GenericComponent*>::iterator it = allAnimations.begin(), end = allAnimations.end(); it != end; ++it)
        {
            delete (*it);
            (*it) = nullptr;
        }
        allAnimations.clear();
    }
    currAnimation = nullptr;
}

void DogAnimComp::Update(double dt)
{
    //currAnimation->Update(dt);
    GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
    PhysicsComponent *zePhysics = dynamic_cast<PhysicsComponent*>(&zeGo->getComponent(PhysicsComponent::g_ID_));
    AnimationComponent *zeAnim = dynamic_cast<AnimationComponent*>(currAnimation);
    switch (hasThePointerBeenActivated)
    {
    case false:
        zeGo->addComponent(AnimationComponent::ID_, currAnimation);
        hasThePointerBeenActivated = true;
        break;
    default:
        break;
    }
    if (zePhysics->getVel().x < -Math::EPSILON)
        //zeGo->getComponent(AnimationComponent::ID_) = *dynamic_cast<AnimationComponent*>(allAnimations[1]);
        zeGo->addComponent(AnimationComponent::ID_, allAnimations[1]);
    else if (zePhysics->getVel().x > Math::EPSILON)
        //zeGo->getComponent(AnimationComponent::ID_) = *dynamic_cast<AnimationComponent*>(allAnimations[0]);
        zeGo->addComponent(AnimationComponent::ID_, allAnimations[0]);
}