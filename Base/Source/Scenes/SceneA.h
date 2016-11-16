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

private:
    CameraBS camera_;
    float m_worldHeight, m_worldWidth;
    float fps;
    std::vector<GameEntity*> m_GoList;
    std::vector<GameEntity*> m_enemy, m_ally;

    Vector3 boundaryOfRoom;
#ifdef _DEBUG
    GameEntity *TestingOutSprite;
#endif
};
