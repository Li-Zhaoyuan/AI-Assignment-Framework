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
	name_ = "DEVIL_SEARCH";
	
}

void Devil_SearchState::Update(double dt)
{
	GameEntity* devil = dynamic_cast<GameEntity*>(owner_of_component);
	PhysicsComponent *zePhysicsStuff = dynamic_cast<PhysicsComponent*>(&(devil)->getComponent(PhysicsComponent::g_ID_));
}

void Devil_SearchState::Exit()
{
}