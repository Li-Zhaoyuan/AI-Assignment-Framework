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

	virtual bool onNotify(const std::string &zeEvent);

private:
    CameraBS camera_;
	int maxDevils;
    float m_worldHeight, m_worldWidth;
    float fps;
	float timerForQ;
	float timerForW;
	Vector3 boundary;
	GameEntity* m_allyBullet, *m_enemyBullet;
	std::vector<GameEntity*> m_GoList, nonActiveBulletList, listToDespawn, tempStorage;
	std::vector<GameEntity*> m_enemy, m_ally;
	size_t background;
	
};
