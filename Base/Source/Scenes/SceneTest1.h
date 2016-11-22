#ifndef SCENE_TEXT1_H
#define SCENE_TEXT1_H

#include "../Classes/SceneEntity.h"
#include "../Classes/GameEntity.h"
#include "../Classes/CameraBS.h"

class SceneTest1 : public SceneEntity
{
public:
    SceneTest1();
    virtual ~SceneTest1();

    virtual void Init();
    virtual void Update(float dt);
    virtual void Render();
    virtual void Exit();

	virtual bool onNotify(GenericEntity &zeEvent);
	virtual bool onNotify(const std::string &zeEvent);

private:
    bool SpawnDog(const Vector3 &zePos);
    bool SpawnZombie(const Vector3 &zePos);
    
    std::vector<GameEntity*> m_GoList, m_InactiveList, tempStorage, nonActiveBulletList, listToDespawn;
	std::vector<GameEntity*> m_enemy, m_ally;
	std::vector<size_t> inactiveObjPos;
	
	CameraBS camera_;
    float m_worldHeight, m_worldWidth;
    float fps;
	//float
	Vector3 boundaryOfRoom;
	unsigned char zeBackground, healthBarID;
    size_t spawnLimitOfDog, spawnLimitOfZombie, dogPresence, zombiePresence;
};

#endif