#include "DevilAnimComponent.h"
#include "AnimationComponent.h"
#include "PhysicsComponent.h"
#include "../Misc/DetectMemoryLeak.h"
#include "../Classes/GameEntity.h"

DevilAnimComp::DevilAnimComp()
{
	if (allAnimations.empty())
	{
		//RIGHT
		AnimationComponent *zeAnimation1 = new AnimationComponent;
		zeAnimation1->Set(3, 5, 10000, 0.5f, true);
		zeAnimation1->unlimitedTimes = true;
		allAnimations.push_back(zeAnimation1);

		//LEFT
		zeAnimation1 = new AnimationComponent;
		zeAnimation1->Set(6, 8, 10000, 0.5f, true);
		zeAnimation1->unlimitedTimes = true;
		allAnimations.push_back(zeAnimation1);

		zeAnimation1 = new AnimationComponent;
		zeAnimation1->Set(0, 2, 10000, 0.5f, true);
		zeAnimation1->unlimitedTimes = true;
		allAnimations.push_back(zeAnimation1);
		/*GameEntity *zeGo1 = dynamic_cast<GameEntity*>(owner_of_component);
		zeGo1->addComponent(AnimationComponent::ID_, allAnimations[1]);*/
	}
	
}

DevilAnimComp::~DevilAnimComp()
{
	GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
	zeGo->eraseComponent(AnimationComponent::ID_);
	if (!allAnimations.empty())
	{
		for (std::vector<GenericComponent*>::iterator it = allAnimations.begin(), end = allAnimations.end(); it != end; ++it)
		{
			delete *it;
			*it = nullptr;
		}
		allAnimations.clear();
	}
}

void DevilAnimComp::Update(double dt)
{
	GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
	PhysicsComponent *zePhysics = dynamic_cast<PhysicsComponent*>(&zeGo->getComponent(PhysicsComponent::g_ID_));
	//zeGo->addComponent(AnimationComponent::ID_, allAnimations[1]);
	/*if (zePhysics->getVel().x > -Math::EPSILON)
		zeGo->addComponent(AnimationComponent::ID_, allAnimations[1]);
	else if (zePhysics->getVel().x < Math::EPSILON)
		zeGo->addComponent(AnimationComponent::ID_, allAnimations[0]);*/
	zeGo->addComponent(AnimationComponent::ID_, allAnimations[2]);
}