#include "MeleeAttackState.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../Gathering of Components/HPandDPComponent.h"

MeleeAttackState::MeleeAttackState()
{

}

MeleeAttackState::~MeleeAttackState()
{

}

void MeleeAttackState::Update(double dt)
{

}

bool MeleeAttackState::onNotify(const int &zeEvent)
{
    if (zeEvent >= 0)
    {

        return true;
    }
    return false;
}