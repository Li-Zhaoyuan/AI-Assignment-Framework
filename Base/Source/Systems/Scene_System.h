/******************************************************************************/
/*!
\file        Scene_System.h
\author      Lee Sek Heng
\par         email: 150629Z@mymail.nyp.edu.sg
\brief
A System that handles all the scene as well as most of the global variables.
GraphicsEntity resides here.
*/
/******************************************************************************/

#ifndef SCENE_SYSTEM_H
#define SCENE_SYSTEM_H

#include "../GenericECS/GenericSystem.h"
#include "..\\Classes\\SingletonTemplate.h"
#include "..\\Classes\\SceneEntity.h"
#include <map>
#include <stack>

/******************************************************************************/
/*!
Class Scene_System:
\brief  Defines a scene system, it's methods for transitioning between scenes,
            a container of those scenes and the Graphics Scene. Inheirits from GenericSystem and SingletonTemplate
*/
/******************************************************************************/
class Scene_System : public GenericSystem, public SingletonTemplate<Scene_System>
{
    friend SingletonTemplate<Scene_System>;
public:
    virtual void Init();    
    virtual void Update(double dt);

    void AddScene(SceneEntity&);
    void RemoveScene(SceneEntity&);

 void SwitchScene(const std::string&);
 bool SwitchToPreviousScene();

    SceneEntity &getCurrScene();
    SceneEntity &getGraphicsScene();

    void setGraphics_Scene(SceneEntity&);
    void clearEverything();
    virtual void Exit();

    SceneEntity &getSpecificScene(const std::string &zeName);

private:
	std::stack<SceneEntity* > SceneHistory;
    std::map<std::string, SceneEntity*> theSceneList;
    SceneEntity *graphics_scene;
    Scene_System() {}
    virtual ~Scene_System() {}
};

#endif