#include "SceneA.h"
#include "../Systems/Scene_System.h"
#include "GraphicsEntity.h"
#include <sstream>
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Gathering of Components/MeshComponent.h"
//TODO: Be Removed
//#include "../StatesStuff/StateMachineComponent.h"
//#include "../StatesStuff/IdleState.h"   
//#include "../Gathering of Components/HPandDPComponent.h"
//TODO: Be Removed
#include "../Misc/NPCBuilder.h"

SceneA::SceneA()
{
    Init();
}

SceneA::~SceneA()
{
    Exit();
}

void SceneA::Init()
{
    GraphicsEntity *zeGraphics = dynamic_cast<GraphicsEntity*>(&Scene_System::accessing().getGraphicsScene());
    name_ = "A";
    camera_.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

    //Calculating aspect ratio
    m_worldHeight = 100.f;
    m_worldWidth = m_worldHeight * (float)Application::GetInstance().cA_WindowWidth / Application::GetInstance().cA_WindowHeight;
    fps = 1;
    zeGraphics->m_renderPass = GraphicsEntity::RENDER_PASS_MAIN;

    // The very reason why we can't see any thing
    Mtx44 ortho;
    ortho.SetToOrtho(-320, 320, -180, 180, -100, 100);
    projectionStack->LoadMatrix(ortho);
    // The very reason why we can't see any thing
    boundaryOfRoom.Set(320, 180, 0);

    m_GoList.push_back(NPCBuilder::BuildZombie("Zombie", boundaryOfRoom, m_enemy, m_ally, Vector3(-55, 0, 0)));
    m_GoList.push_back(NPCBuilder::BuildDog("Dog", boundaryOfRoom, m_enemy, m_ally, Vector3(0,20,0)));
    m_GoList.push_back(NPCBuilder::BuildZombie("Zombie", boundaryOfRoom, m_enemy, m_ally, Vector3(140,100, 0)));
    m_GoList.push_back(NPCBuilder::BuildZombie("Zombie", boundaryOfRoom, m_enemy, m_ally, Vector3(140, -150, 0)));
    m_GoList.push_back(NPCBuilder::BuildDog("Dog", boundaryOfRoom, m_enemy, m_ally, Vector3(-200, 20, 0)));
}

void SceneA::Update(float dt)
{
#ifdef _DEBUG
    // TODO: Remove it when it is not debugging
    GraphicsEntity *zeGraphics = dynamic_cast<GraphicsEntity*>(&Scene_System::accessing().getGraphicsScene());
    zeGraphics->Update(dt);
    // TODO: Remove it when it is not debugging
#endif
    fps = 1 / dt;
    if (Application::IsKeyPressed(VK_NUMPAD2))
        Scene_System::accessing().SwitchScene("B");

    for (std::vector<GameEntity*>::iterator it = m_GoList.begin(), end = m_GoList.end(); it != end; ++it)
    {
        (*it)->Update(dt);
    }
}

void SceneA::Render()
{
    GraphicsEntity *zeGraphics = dynamic_cast<GraphicsEntity*>(&Scene_System::accessing().getGraphicsScene());

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Application::GetInstance().cA_WindowWidth, Application::GetInstance().cA_WindowHeight);

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(zeGraphics->m_programID);

    //pass light depth texture
    //zeGraphics->m_lightDepthFBO.BindForReading(GL_TEXTURE8);
    //glUniform1i(zeGraphics->m_parameters[GraphicsEntity::U_SHADOW_MAP], 8);

    //Mtx44 perspective;
    //perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
    //projectionStack->LoadMatrix(perspective);
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

    //modelStack->PushMatrix();
    //modelStack->Translate(-50, -50, 0);
    //modelStack->Scale(50, 50, 10);
    //zeGraphics->RenderMesh(2, false);
    //modelStack->PopMatrix();

    //modelStack->PushMatrix();
    //modelStack->Scale(100, 100, 1);
    //zeGraphics->RenderText("Sek Heng Stuff", Color(0, 1, 0));
    //modelStack->PopMatrix();

    for (std::vector<GameEntity*>::iterator it = m_GoList.begin(), end = m_GoList.end(); it != end; ++it)
    {
        //switch ((*it)->seeComponentActive(MeshComponent::g_CompID_.getValue()))
        switch ((*it)->seeComponentActive(MyMeshComponent::ID_))
        {
        case true: 
        {
            modelStack->PushMatrix();
            PhysicsComponent *zePhysicsStuff = dynamic_cast<PhysicsComponent*>(&(*it)->getComponent(PhysicsComponent::g_ID_));
            MeshComponent *zeMeshID = dynamic_cast<MeshComponent*>(&(*it)->getComponent(MeshComponent::g_CompID_.getValue()));
            //MyMeshComponent *zeMesh = dynamic_cast<MyMeshComponent*>(&(*it)->getComponent(MyMeshComponent::ID_));
            modelStack->Translate(zePhysicsStuff->getPos().x, zePhysicsStuff->getPos().y, zePhysicsStuff->getPos().z);
                // Debuggin Stuff
                modelStack->PushMatrix();
                modelStack->Translate(0, (zePhysicsStuff->getSize().y / 2) + 5.f, 0);
                modelStack->Scale(15, 15, 1);
                zeGraphics->RenderText((*it)->getName(), Color(1, 0, 0));
                modelStack->PopMatrix();
                // Debuggin Stuff
            modelStack->Scale(zePhysicsStuff->getSize().x, zePhysicsStuff->getSize().y, zePhysicsStuff->getSize().z);
            zeGraphics->RenderMesh(zeMeshID->getMeshID(), false);
            //zeGraphics->RenderMesh(*zeMesh, false);
            modelStack->PopMatrix();
        }
            break;
        default:
            break;
        }
    }

    //zeGraphics->SetHUD(true);
    viewStack->LoadIdentity();
    std::ostringstream ss;
    ss << "FPS:" << fps;
    zeGraphics->RenderTextOnScreen(ss.str(), Color(0, 1, 0), 15, -boundaryOfRoom.x, -boundaryOfRoom.y);
    //zeGraphics->SetHUD(false);
}

void SceneA::Exit()
{
    for (std::vector<GameEntity*>::iterator it = m_GoList.begin(), end = m_GoList.end(); it != end; ++it)
    {
        delete *it;
        *it = nullptr;
    }
    m_GoList.clear();
    m_ally.clear();
    m_enemy.clear();
}

