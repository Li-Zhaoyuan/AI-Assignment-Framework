#pragma once

#include "../Classes/GameEntity.h"
#include "../GenericECS/GenericComponent.h"

class AllyEnemyComponent : public GenericComponent
{
public:
    AllyEnemyComponent();
    virtual ~AllyEnemyComponent();

    virtual void Init();

    AllyEnemyComponent &setAllyList(std::vector<GameEntity*> &zeAlly);
    AllyEnemyComponent &setEnemyList(std::vector<GameEntity*> &zeEnemy);

    static const unsigned char ID_ = 6;

    std::vector<GameEntity*> *m_allyList, *m_enemyList;
};