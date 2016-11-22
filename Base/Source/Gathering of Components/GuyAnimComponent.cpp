#include "GuyAnimComponent.h"
#include "AnimationComponent.h"
#include "PhysicsComponent.h"
#include "../StatesStuff/StateMachineComponent.h"
#include "../Misc/DetectMemoryLeak.h"
#include "../Classes/GameEntity.h"

GuyAnimComp::GuyAnimComp()
{
	if (allAnimations.empty())
	{
		//RIGHT
		AnimationComponent *zeAnimation1 = new AnimationComponent;
		zeAnimation1->Set(0, 1, 10000, 0.5f, true);
		zeAnimation1->unlimitedTimes = true;
		allAnimations.push_back(zeAnimation1);

		//LEFT
		zeAnimation1 = new AnimationComponent;
		zeAnimation1->Set(2, 3, 10000, 0.5f, true);
		zeAnimation1->unlimitedTimes = true;
		allAnimations.push_back(zeAnimation1);
	}
}

GuyAnimComp::~GuyAnimComp()
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

void GuyAnimComp::Update(double dt)
{
	GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
	PhysicsComponent *zePhysics = dynamic_cast<PhysicsComponent*>(&zeGo->getComponent(PhysicsComponent::g_ID_));
	StateMachineComponent *currState = dynamic_cast<StateMachineComponent*>(&zeGo->getComponent(StateMachineComponent::ID_.getValue()));

	if (currState->getCurrentState().getName() == currState->getSpecificStates(3).getName())
	{
		if (zePhysics->getVel().x > -Math::EPSILON)
			zeGo->addComponent(AnimationComponent::ID_, allAnimations[0]);
		else if (zePhysics->getVel().x < Math::EPSILON)
			zeGo->addComponent(AnimationComponent::ID_, allAnimations[1]);
	}
	else
	{
		if (zePhysics->getVel().x > -Math::EPSILON)
			zeGo->addComponent(AnimationComponent::ID_, allAnimations[1]);
		else if (zePhysics->getVel().x < Math::EPSILON)
			zeGo->addComponent(AnimationComponent::ID_, allAnimations[0]);
	}
}