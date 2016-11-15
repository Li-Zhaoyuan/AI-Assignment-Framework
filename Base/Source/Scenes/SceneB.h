#pragma once

#include "../Classes/SceneEntity.h"
#include "../Classes/GameEntity.h"
#include "../Classes/CameraBS.h"

class SceneB : public SceneEntity
{
public:
    SceneB();
    virtual ~SceneB();

    virtual void Init();
    virtual void Update(float dt);
    virtual void Render();
    virtual void Exit();

private:
    CameraBS camera_;
    float m_worldHeight, m_worldWidth;
    float fps;
	Vector3 boundary;
	GameEntity* m_allyBullet, *m_enemyBullet;
	std::vector<GameEntity*> m_GoList;
	std::vector<GameEntity*> m_enemy, m_ally;
	size_t background;
	
};
