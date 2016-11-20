#include "ZombieAnimComp.h"
#include "AnimationComponent.h"
#include "PhysicsComponent.h"
#include "../Misc/DetectMemoryLeak.h"
#include "../Classes/GameEntity.h"

std::vector<GenericComponent*> ZombieAnimComp::allAnimations;

ZombieAnimComp::ZombieAnimComp()
{
    if (allAnimations.empty())
    {
        //RIGHT
        AnimationComponent *zeAnimation1 = new AnimationComponent;
        allAnimations.push_back(zeAnimation1);

        //LEFT
    }
}

ZombieAnimComp::~ZombieAnimComp()
{
    GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
    zeGo->eraseComponent(AnimationComponent::ID_);
    if (!allAnimations.empty())
    {
        allAnimations.clear();
    }
}

void ZombieAnimComp::Update(double dt)
{

}