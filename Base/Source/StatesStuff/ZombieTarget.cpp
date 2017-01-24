#include "ZombieTarget.h"
#include "MyMath.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Classes/GameEntity.h"
#include "../Gathering of Components/SpeedComponent.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../Gathering of Components/ZombieReactComponent.h" 
#include "MeleeAttackState.h"

ZombieTarget::ZombieTarget()
{
    name_ = ": TARGET";
    changedName = false;
	//isReplying = false;
    originalOwnerName = "";
    chancesOfAction = 1000;
    originalDistToActivate = distToActivate = 0;
    zeVictim = nullptr;
}

ZombieTarget::~ZombieTarget()
{
    Exit();
}

void ZombieTarget::Update(double dt)
{
    switch (changedName)
    {
    case false:
    {
        std::string zeName = owner_of_component->getName();
        originalOwnerName = zeName;
		if (isReplying)
			zeName.append("[reply]");
        zeName.append(name_);
        owner_of_component->setName(zeName);
        changedName = true;
    }
    break;
    default:
        break;
    }
	//std::string str = getOriginalOwnerName();
    GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
    PhysicsComponent *zePhysics = dynamic_cast<PhysicsComponent*>(&zeGo->getComponent(PhysicsComponent::g_ID_));
    PhysicsComponent *enemyPhysics = dynamic_cast<PhysicsComponent*>(zeVictim);
	ZombieReactComponent *zeReactComp = dynamic_cast<ZombieReactComponent*>(&zeGo->getComponent(ZombieReactComponent::ID_));
	if (!isReplying)// when not replying tell the react component that it is not reacting
	{
		zeReactComp->onNotify(0);
	}
    if ((!enemyPhysics || ((zePhysics->getPos() - enemyPhysics->getPos()).LengthSquared() > influenceRadius * influenceRadius))
		&& isReplying == false)
    {
        FSM_->switchState(0);
        zePhysics->setVel(Vector3(0, 0, 0));
    }
    else
    {
        SpeedComponent *zeSpeed = dynamic_cast<SpeedComponent*>(&zeGo->getComponent(SpeedComponent::ID_));
		if (enemyPhysics == NULL)
		{
			isReplying = false;
			return;
		}
		Vector3 sqOfDist = enemyPhysics->getPos() - zePhysics->getPos();
        if (sqOfDist.LengthSquared() <= distToActivate * distToActivate)
        {
            switch (Math::RandIntMinMax(1, chancesOfAction))
            {
            case 1:
                FSM_->getSpecificStates(5).onNotify(*zeVictim);
                FSM_->switchState(5);
                break;
            default:
                break;
            }
            distToActivate = 0;
        }
        else {
            MeleeAttackState *zeAttack = dynamic_cast<MeleeAttackState*>(&FSM_->getSpecificStates(MeleeAttackState::ID_));
            if (sqOfDist.LengthSquared() <= zeAttack->getAttackRadius() * zeAttack->getAttackRadius())
            {
                FSM_->getSpecificStates(MeleeAttackState::ID_).onNotify(*zeVictim);
                FSM_->switchState(MeleeAttackState::ID_);
				isReplying = false;
            }
            zePhysics->setVel(sqOfDist.Normalize() * zeSpeed->getSpeed());
			
        }
    }
}

void ZombieTarget::Exit()
{
    zeVictim = nullptr;
    changedName = false;
	//isReplying = false;
    if (originalOwnerName != "")
        owner_of_component->setName(originalOwnerName);
    distToActivate = originalDistToActivate;
}

bool ZombieTarget::onNotify(const float &zeEvent)
{
    if (zeEvent > Math::EPSILON)
    {
        influenceRadius = zeEvent;
        return true;
    }
    else if (zeEvent < -Math::EPSILON)
    {
        distToActivate = -zeEvent;
        originalDistToActivate = -zeEvent;
        return true;
    }
    return false;
}

bool ZombieTarget::onNotify(GenericComponent &zeEvent)
{
	if (!zeVictim) {
		PhysicsComponent *zeVictimPhy = dynamic_cast<PhysicsComponent*>(&zeEvent);
		if (zeVictimPhy)
		{
			zeVictim = zeVictimPhy;
		}
		else
		{
			GameEntity *zeVictimEntity = dynamic_cast<GameEntity*>(&zeEvent.getOwner());
			zeVictim = dynamic_cast<PhysicsComponent*>(&zeVictimEntity->getComponent(PhysicsComponent::g_ID_));
		}
		return true;
	}
	return false;
}

bool ZombieTarget::onNotify(const int &zeEvent)
{
    if (zeEvent > 0)
    {
        chancesOfAction = zeEvent;
    }
    return false;
}

bool ZombieTarget::onNotify(const std::string &zeEvent)
{
	if (zeEvent.find("name") != std::string::npos)    // Check to see if the event is for the guy to go. If so, extract the position out from the string
	{
		std::string anotherStr = zeEvent.substr(5);//hardcoding that 5 coz of name:
		GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
		AllyEnemyComponent *findingEnemy = dynamic_cast<AllyEnemyComponent*>(&zeGo->getComponent(AllyEnemyComponent::ID_));
		for (std::vector<GameEntity*>::iterator it = findingEnemy->m_enemyList->begin(), end = findingEnemy->m_enemyList->end(); it != end; ++it)
		{
			StateMachineComponent* fsm = dynamic_cast<StateMachineComponent*>(&(*it)->getComponent(StateMachineComponent::ID_.getValue()));
			if (zeEvent.find(fsm->getCurrentState().getOriginalOwnerName()) != std::string::npos)
			{
				zeVictim = dynamic_cast<PhysicsComponent*>(&(*it)->getComponent(PhysicsComponent::g_ID_));
				isReplying = true;
				return true;
			}
		}
		return false;
	}
	return false;
}