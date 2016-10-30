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

private:
    CameraBS camera_;
    float m_worldHeight, m_worldWidth;
    float fps;
};

#endif