#include "Devil_SearchState.h"
#include "..\Gathering of Components\PhysicsComponent.h"
#include "..\Classes\GameEntity.h"

Devil_SearchState::Devil_SearchState()
{
	Init();
}

Devil_SearchState::~Devil_SearchState()
{

}

void Devil_SearchState::Init()
{
	name_ = " : SEARCH";
	hasNameChange = false;
	timer = 0;
	searchVel.SetZero();
}

void Devil_SearchState::Update(double dt)
{
	switch (hasNameChange)
	{
	case false:
	{
		std::string newName = owner_of_component->getName();
		newName.append(name_);
		owner_of_component->setName(newName);
		hasNameChange = true;
	}
	break;
	default:
		break;
	}
	GameEntity* devil = dynamic_cast<GameEntity*>(owner_of_component);
	PhysicsComponent *zePhysicsStuff = dynamic_cast<PhysicsComponent*>(&(devil)->getComponent(PhysicsComponent::g_ID_));

	//int randomDir = rand() % 4 + 1;
	timer += (float)dt;
	if (timer >= 0.5f)
	{
		searchVel.x = Math::RandFloatMinMax(-150.f, 150.f);
		searchVel.y = Math::RandFloatMinMax(-150.f, 150.f);
		timer = 0;
	}
	
	if ((zePhysicsStuff->getPos().x + zePhysicsStuff->getVel().x * dt) > zePhysicsStuff->getBoundary().x
		|| (zePhysicsStuff->getPos().x + zePhysicsStuff->getVel().x * dt) < -zePhysicsStuff->getBoundary().x)
		searchVel.x = -searchVel.x;
	if ((zePhysicsStuff->getPos().y + zePhysicsStuff->getVel().y * dt) > zePhysicsStuff->getBoundary().y
		|| (zePhysicsStuff->getPos().y + zePhysicsStuff->getVel().y * dt) < -zePhysicsStuff->getBoundary().y)
		searchVel.y = -searchVel.y;
	//zePhysicsStuff->getPos().x
	zePhysicsStuff->setVel(Vector3(searchVel.x, searchVel.y, 0));
	
	
}

void Devil_SearchState::Exit()
{
}