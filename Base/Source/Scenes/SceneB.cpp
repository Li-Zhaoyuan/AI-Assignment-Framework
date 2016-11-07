#include "SceneB.h"
#include "../Systems/Scene_System.h"
#include "GraphicsEntity.h"
#include <sstream>
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Gathering of Components/MeshComponent.h"
#include "../StatesStuff/StateMachineComponent.h"
#include "../StatesStuff/Devil_SearchState.h"   
#include "../Gathering of Components/HPandDPComponent.h"


SceneB::SceneB()
{
    Init();
}

SceneB::~SceneB()
{
    Exit();
}

void SceneB::Init()
{
    GraphicsEntity *zeGraphics = dynamic_cast<GraphicsEntity*>(&Scene_System::accessing().getGraphicsScene());
    name_ = "B";
    camera_.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

    //Calculating aspect ratio
    m_worldHeight = 100.f;
    m_worldWidth = m_worldHeight * (float)Application::GetInstance().cA_WindowWidth / Application::GetInstance().cA_WindowHeight;
    fps = 1;
    zeGraphics->m_renderPass = GraphicsEntity::RENDER_PASS_MAIN;

    // The very reason why we can't see any thing
    Mtx44 ortho;
    ortho.SetToOrtho(-400, 400, -300, 300, -100, 100);
    projectionStack->LoadMatrix(ortho);
    // The very reason why we can't see any thing
	//Devil_SearchState
	Devil = new GameEntity();
	Devil->setName("Devil");
	MeshComponent *devilMesh = new MeshComponent();
	devilMesh->onNotify(zeGraphics->getMeshID("redCube"));
	Devil->addComponent(MeshComponent::g_CompID_.getValue(), devilMesh);
	PhysicsComponent *devilPhysic = new PhysicsComponent();
	devilPhysic->setSize(Vector3(50, 50, 1));
	devilPhysic->setYrotation(0);
	Devil->addComponent(PhysicsComponent::g_ID_, devilPhysic);
	
	StateMachineComponent *devilFSM = new StateMachineComponent();
	Devil->addComponent(StateMachineComponent::ID_.getValue(), devilFSM);
	devilFSM->addStates(*new Devil_SearchState(), Devil_SearchState::ID_);
	Devil->addComponent(HPandDPComponent::ID_, new HPandDPComponent(100, 15));
	
}

void SceneB::Update(float dt)
{
#ifdef _DEBUG
    // TODO: Remove it when it is not debugging
    GraphicsEntity *zeGraphics = dynamic_cast<GraphicsEntity*>(&Scene_System::accessing().getGraphicsScene());
    zeGraphics->Update(dt);
    // TODO: Remove it when it is not debugging
#endif
    fps = 1 / dt;
    if (Application::IsKeyPressed(VK_NUMPAD1))
        Scene_System::accessing().SwitchScene("A");

}

void SceneB::Render()
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

    modelStack->PushMatrix();
    modelStack->Translate(-50, -50, 0);
    modelStack->Scale(50, 50, 10);
    zeGraphics->RenderMesh(2, false);
    modelStack->PopMatrix();

    modelStack->PushMatrix();
    modelStack->Scale(100, 100, 1);
    zeGraphics->RenderText("Zhao Yuan Stuff", Color(0, 1, 0));
    modelStack->PopMatrix();

	modelStack->PushMatrix();
	PhysicsComponent *zePhysicsStuff = dynamic_cast<PhysicsComponent*>(&(Devil)->getComponent(PhysicsComponent::g_ID_));
	MeshComponent *zeMeshID = dynamic_cast<MeshComponent*>(&(Devil)->getComponent(MeshComponent::g_CompID_.getValue()));
	modelStack->Translate(zePhysicsStuff->getPos().x, zePhysicsStuff->getPos().y, zePhysicsStuff->getPos().z);
	modelStack->Scale(zePhysicsStuff->getSize().x, zePhysicsStuff->getSize().y, zePhysicsStuff->getSize().z);
	zeGraphics->RenderMesh(zeMeshID->getMeshID(), false);
	modelStack->PopMatrix();

    //zeGraphics->SetHUD(true);
    viewStack->LoadIdentity();
    std::ostringstream ss;
    ss << "FPS:" << fps;
    zeGraphics->RenderTextOnScreen(ss.str(), Color(0, 1, 0), 10, 0, 0);
    //zeGraphics->SetHUD(false);
}

void SceneB::Exit()
{
	delete Devil;
	Devil = nullptr;
}

