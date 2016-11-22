#include "IdleState.h"
#include "../Misc/GlobalFunctions.h"
#include "MyMath.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Gathering of Components/CollisionComponent.h"
#include <sstream>

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
    GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
    PhysicsComponent *zePhysics = dynamic_cast<PhysicsComponent*>(&zeGo->getComponent(PhysicsComponent::g_ID_));
    AllyEnemyComponent *zeEnemyStuff = dynamic_cast<AllyEnemyComponent*>(&zeGo->getComponent(AllyEnemyComponent::ID_));
    for (std::vector<GameEntity*>::iterator it = zeEnemyStuff->m_enemyList->begin(), end = zeEnemyStuff->m_enemyList->end(); it != end; ++it)
    {
        GameEntity *zeEnemy = (*it);
        if (zeEnemy->seeComponentActive(4))
        {
            PhysicsComponent *enemyPhy = dynamic_cast<PhysicsComponent*>(&(*it)->getComponent(PhysicsComponent::g_ID_));
            if ((zePhysics->getPos() - enemyPhy->getPos()).LengthSquared() <= influenceRadius * influenceRadius)
            {
                FSM_->switchState(1);
                FSM_->getCurrentState().onNotify(*enemyPhy);
                break;
            }
        }
    }
}

void IdleState::Exit()
{
    changedName = false;
    if (originalOwnerName != "")
        owner_of_component->setName(originalOwnerName);
}

bool IdleState::onNotify(const float &zeEvent)
{
    if (zeEvent > Math::EPSILON)
    {
        influenceRadius = zeEvent;
    }
    return false;
}

bool IdleState::onNotify(GenericComponent &zeEvent)
{
	CollisionComponent *zeBullet = dynamic_cast<CollisionComponent*>(&zeEvent);
	if (zeBullet && checkWhetherTheWordInThatString("Zombie", originalOwnerName))
	{
		FSM_->switchState(2);
		std::ostringstream ss;
		GameEntity *zeGo = dynamic_cast<GameEntity*>(&zeBullet->getOwner());
		PhysicsComponent *zeBulletPos = dynamic_cast<PhysicsComponent*>(&zeGo->getComponent(PhysicsComponent::g_ID_));
		GameEntity *ownGo = dynamic_cast<GameEntity*>(owner_of_component);
		PhysicsComponent *ownPhysics = dynamic_cast<PhysicsComponent*>(&ownGo->getComponent(PhysicsComponent::g_ID_));
		Vector3 zeOppDir = -zeBulletPos->getVel();
		zeOppDir.Normalize();
		zeOppDir *= 70;
		ss << "GO:" << zeOppDir.x + ownPhysics->getPos().x << "," << zeOppDir.y + ownPhysics->getPos().y << "," << zeOppDir.z + ownPhysics->getPos().z;
		FSM_->getCurrentState().onNotify(ss.str());
		return true;
	}
	return false;
}