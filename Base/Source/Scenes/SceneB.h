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
};
