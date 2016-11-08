#include "AllyEnemyComponent.h"

AllyEnemyComponent::AllyEnemyComponent()
{
    Init();
}

AllyEnemyComponent::~AllyEnemyComponent()
{
    m_allyList = nullptr;
    m_enemyList = nullptr;
}

void AllyEnemyComponent::Init()
{
    m_allyList = nullptr;
    m_enemyList = nullptr;
}

AllyEnemyComponent &AllyEnemyComponent::setAllyList(std::vector<GameEntity*> &zeAlly)
{
    m_allyList = &zeAlly;
    return *this;
}

AllyEnemyComponent &AllyEnemyComponent::setEnemyList(std::vector<GameEntity*> &zeEnemy)
{
    m_enemyList = &zeEnemy;
    return *this;
}