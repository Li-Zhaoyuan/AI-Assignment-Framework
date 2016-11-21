#pragma once

#include "../Classes/SceneEntity.h"
#include "../Classes/GameEntity.h"
#include "../Classes/CameraBS.h"

class SceneA : public SceneEntity
{
public:
    SceneA();
    virtual ~SceneA();

    virtual void Init();
    virtual void Update(float dt);
    virtual void Render();
    virtual void Exit();

    virtual bool onNotify(GenericEntity &zeEvent);

private:
    bool SpawnDog(const Vector3 &zePos);
    bool SpawnZombie(const Vector3 &zePos);

    CameraBS camera_;
    float m_worldHeight, m_worldWidth;
    float fps;
    std::vector<GameEntity*> m_GoList, m_InactiveList, tempStorage;
    std::vector<GameEntity*> m_enemy, m_ally;
    std::vector<size_t> activeObjPos, inactiveObjPos;

    Vector3 boundaryOfRoom;
#ifdef _DEBUG
    GameEntity *TestingOutSprite;
#endif
    unsigned char zeBackground, healthBarID;
};
