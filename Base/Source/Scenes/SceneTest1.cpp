#include "SceneTest1.h"
#include "../Systems/Scene_System.h"
#include "GraphicsEntity.h"
#include <sstream>

SceneTest1::SceneTest1()
{
    Init();
}

SceneTest1::~SceneTest1()
{
    Exit();
}

void SceneTest1::Init()
{
    GraphicsEntity *zeGraphics = dynamic_cast<GraphicsEntity*>(&Scene_System::accessing().getGraphicsScene());
    name_ = "ze first scene test";
    camera_.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

    //Calculating aspect ratio
    m_worldHeight = 100.f;
    m_worldWidth = m_worldHeight * (float)Application::GetInstance().cA_WindowWidth / Application::GetInstance().cA_WindowHeight;
    fps = 1;
    zeGraphics->m_renderPass = GraphicsEntity::RENDER_PASS_MAIN;

    zeGraphics->projectionStack = projectionStack;
    zeGraphics->SetHUD(true);
    Mtx44 projection;
    projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
    projectionStack->LoadMatrix(projection);
}

void SceneTest1::Update(float dt)
{
    GraphicsEntity *zeGraphics = dynamic_cast<GraphicsEntity*>(&Scene_System::accessing().getGraphicsScene());
    fps = 1 / dt;
}

void SceneTest1::Render()
{
    GraphicsEntity *zeGraphics = dynamic_cast<GraphicsEntity*>(&Scene_System::accessing().getGraphicsScene());
    zeGraphics->Render();

    // camera_ matrix
    viewStack->LoadIdentity();
    viewStack->LookAt(
        camera_.position.x, camera_.position.y, camera_.position.z,
        camera_.target.x, camera_.target.y, camera_.target.z,
        camera_.up.x, camera_.up.y, camera_.up.z
        );
    // Model matrix : an identity matrix (model will be at the origin)
    modelStack->LoadIdentity();

    zeGraphics->RenderMesh(0, false);

    std::ostringstream ss;
    ss << "FPS:" << fps;
    zeGraphics->RenderTextOnScreen(ss.str(), Color(0, 1, 0), 40, 10, 10);
}

void SceneTest1::Exit()
{

}

