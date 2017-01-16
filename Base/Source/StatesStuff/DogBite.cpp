#include "DogBite.h"
#include "MyMath.h"
#include "../Classes/GameEntity.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Gathering of Components/HPandDPComponent.h"
#include <sstream>
#include "../Systems/MessageSystem.h"
DogBite::DogBite()
{
    Init();
}

DogBite::~DogBite()
{
    Exit();
}

void DogBite::Init()
{
    zeVictim = nullptr;
    chanceToActivate = 100000;
    timeCounter = 0;
    attackDelay = 0;
    name_ = "BITE";
    changedName = false;
}

void DogBite::Update(double dt)
{
#ifdef _DEBUG
    assert(zeVictim);
#endif
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
    timeCounter += (float)dt;
    if (timeCounter >= attackDelay)
    {
        GameEntity *zeGo = dynamic_cast<GameEntity*>(owner_of_component);
        PhysicsComponent *zePhysics = dynamic_cast<PhysicsComponent*>(&zeGo->getComponent(PhysicsComponent::g_ID_));
        switch (zePhysics->getVel().IsZero())
        {
        case false:
            zePhysics->getVel().SetZero();
            break;
        default:
            break;
        }

        GameEntity *zeEnemy = dynamic_cast<GameEntity*>(&zeVictim->getOwner());
        switch (Math::RandIntMinMax(1, chanceToActivate))
        {
        case 1:
        {
            HPandDPComponent *zeMyDMG = dynamic_cast<HPandDPComponent*>(&zeGo->getComponent(HPandDPComponent::ID_));
            zeEnemy->getComponent(HPandDPComponent::ID_).onNotify(-zeMyDMG->getDamage());
			HPandDPComponent *enemyHP = dynamic_cast<HPandDPComponent*>(&zeEnemy->getComponent(HPandDPComponent::ID_));
			if (enemyHP->getHealth() < 50
				&& zeEnemy->getName().find("Devil") != std::string::npos)
			{
				std::ostringstream ss;
				ss.str("");
				if (zeEnemy->getName().find("Devil<LEADER>") != std::string::npos)
					ss << "I Need Assistance!|Devil<LDR>|Zombie&Devil<LDR>|name:" << originalOwnerName;
				else
					ss << "I Need Assistance!|Devil|Zombie&Devil<LDR>|name:" << originalOwnerName;
				MessageSystem::accessing().onNotify(ss.str());
			}
        }
            break;
        default:
            PhysicsComponent *zeEnemyPhy = dynamic_cast<PhysicsComponent*>(zeVictim);
            Vector3 sqDist = zePhysics->getPos() - zeEnemyPhy->getPos();
            sqDist.Normalize();
            std::ostringstream ss;
            ss << "GO:" << sqDist.x * influenceRadius << "," << sqDist.y * influenceRadius << "," << 0;
            FSM_->getSpecificStates(1).onNotify(ss.str());
            FSM_->switchState(1);
            break;
        }
        timeCounter = 0;
    }
}

void DogBite::Exit()
{
    zeVictim = nullptr;
    changedName = false;
    if (originalOwnerName != "")
        owner_of_component->setName(originalOwnerName);
}

bool DogBite::onNotify(GenericComponent &zeEvent)
{
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
    timeCounter = attackDelay;
    return true;
}

bool DogBite::onNotify(const int &zeEvent)
{
    if (zeEvent > 0)
    {
        chanceToActivate = zeEvent;
        return true;
    }
    return false;
}

bool DogBite::onNotify(const float &zeEvent)
{
    if (zeEvent > Math::EPSILON)
    {
        influenceRadius = zeEvent;
        return true;
    }
    else if (zeEvent < -Math::EPSILON)
    {
        attackDelay = -zeEvent;
        return true;
    }
    return false;
}