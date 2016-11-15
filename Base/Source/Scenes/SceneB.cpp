#include "SceneB.h"
#include "../Systems/Scene_System.h"
#include "GraphicsEntity.h"
#include <sstream>
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Gathering of Components/MeshComponent.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../StatesStuff/StateMachineComponent.h"
#include "../StatesStuff/Devil_SearchState.h"   
#include "../StatesStuff/Devil_AttackState.h"   
#include "../StatesStuff/Guy_PatrolState.h"   
#include "../StatesStuff/Guy_EscapeState.h"   
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
	boundary.Set(320, 180, 0);
    Mtx44 ortho;
	ortho.SetToOrtho(-320, 320, -180, 180, -100, 100);
    projectionStack->LoadMatrix(ortho);
    // The very reason why we can't see any thing
	//Devil_SearchState
	GameEntity *Devil = new GameEntity();
	Devil->setName("Devil");
	MeshComponent *devilMesh = new MeshComponent();
	devilMesh->onNotify(zeGraphics->getMeshID("redCube"));
	Devil->addComponent(MeshComponent::g_CompID_.getValue(), devilMesh);
	PhysicsComponent *devilPhysic = new PhysicsComponent();
	devilPhysic->setSize(Vector3(25, 25, 1));
	devilPhysic->setYrotation(0);
	devilPhysic->setBoundary(boundary);
	devilPhysic->setPos(Vector3(0, 0, 0));
	Devil->addComponent(PhysicsComponent::g_ID_, devilPhysic);
	
	StateMachineComponent *devilFSM = new StateMachineComponent();
	Devil->addComponent(StateMachineComponent::ID_.getValue(), devilFSM);
	devilFSM->addStates(*new Devil_SearchState(), Devil_SearchState::ID_);
	devilFSM->addStates(*new Devil_AttackState(), Devil_AttackState::ID_);
	Devil->addComponent(HPandDPComponent::ID_, new HPandDPComponent(100, 15));

	AllyEnemyComponent *DeviltoRecogniseEnemyAlly = new AllyEnemyComponent();
	DeviltoRecogniseEnemyAlly->setAllyList(m_enemy).setEnemyList(m_ally);
	Devil->addComponent(AllyEnemyComponent::ID_, DeviltoRecogniseEnemyAlly);


	m_GoList.push_back(Devil);
	m_enemy.push_back(Devil);

	GameEntity *Guy = new GameEntity();
	Guy->setName("Guy");
	MeshComponent *guyMesh = new MeshComponent();
	guyMesh->onNotify(zeGraphics->getMeshID("whiteQuad"));
	Guy->addComponent(MeshComponent::g_CompID_.getValue(), guyMesh);
	PhysicsComponent *guyPhysic = new PhysicsComponent();
	guyPhysic->setSize(Vector3(25, 25, 1));
	guyPhysic->setYrotation(0);
	guyPhysic->setBoundary(boundary);
	guyPhysic->setPos(Vector3(150, 0, 0));
	Guy->addComponent(PhysicsComponent::g_ID_, guyPhysic);

	StateMachineComponent *guyFSM = new StateMachineComponent();
	Guy->addComponent(StateMachineComponent::ID_.getValue(), guyFSM);
	guyFSM->addStates(*new Guy_PatrolState(), Guy_PatrolState::ID_);
	guyFSM->addStates(*new Guy_EscapeState(), Guy_EscapeState::ID_);
	Guy->addComponent(HPandDPComponent::ID_, new HPandDPComponent(100, 15));
	
	AllyEnemyComponent *GuytoRecogniseEnemyAlly = new AllyEnemyComponent;
	GuytoRecogniseEnemyAlly->setAllyList(m_ally).setEnemyList(m_enemy);
	Guy->addComponent(AllyEnemyComponent::ID_, GuytoRecogniseEnemyAlly);


	m_GoList.push_back(Guy);
	m_ally.push_back(Guy);

	//m_allyBullet, m_enemyBullet;
	background = zeGraphics->getMeshID("sceneBBackground");
	
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
	for (std::vector<GameEntity*>::iterator it = m_GoList.begin(), end = m_GoList.end(); it != end; ++it)
	{
		(*it)->Update(dt);
	}
	
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


    modelStack->PushMatrix();
    modelStack->Translate(0, 0, -1);
	modelStack->Scale(boundary.x*2, boundary.x *2, 1);
	zeGraphics->RenderMesh(background, false);
    modelStack->PopMatrix();


	for (std::vector<GameEntity*>::iterator it = m_GoList.begin(), end = m_GoList.end(); it != end; ++it)
	{
		switch ((*it)->seeComponentActive(MeshComponent::g_CompID_.getValue()))
		{
		case true:
		{
					 modelStack->PushMatrix();
					 PhysicsComponent *zePhysicsStuff = dynamic_cast<PhysicsComponent*>(&(*it)->getComponent(PhysicsComponent::g_ID_));
					 MeshComponent *zeMeshID = dynamic_cast<MeshComponent*>(&(*it)->getComponent(MeshComponent::g_CompID_.getValue()));
					 HPandDPComponent*zeHP = dynamic_cast<HPandDPComponent*>(&(*it)->getComponent(HPandDPComponent::ID_));
					 modelStack->Translate(zePhysicsStuff->getPos().x, zePhysicsStuff->getPos().y, zePhysicsStuff->getPos().z);
					 // Debuggin Stuff
					 modelStack->PushMatrix();
					 modelStack->Translate(-25, (zePhysicsStuff->getSize().y / 2) + 5.f, 0);
					 modelStack->Scale(10, 10, 1);
					 zeGraphics->RenderText((*it)->getName(), Color(1, 0, 0));
					 modelStack->PopMatrix();

					 modelStack->PushMatrix();
					 modelStack->Translate(-25, -(zePhysicsStuff->getSize().y / 2) - 5.f, 0);
					 modelStack->Scale(10, 10, 1);
					 zeGraphics->RenderText(std::to_string(zeHP->getHealth()), Color(1, 0, 0));
					 modelStack->PopMatrix();
					 // Debuggin Stuff
					 modelStack->Scale(zePhysicsStuff->getSize().x, zePhysicsStuff->getSize().y, zePhysicsStuff->getSize().z);
					 zeGraphics->RenderMesh(zeMeshID->getMeshID(), false);
					 modelStack->PopMatrix();

					 
		}
			break;
		default:
			break;
		}
	}


    //zeGraphics->SetHUD(true);
    viewStack->LoadIdentity();
    /*std::ostringstream ss;
    ss << "FPS:" << fps;
    zeGraphics->RenderTextOnScreen(ss.str(), Color(0, 1, 0), 10, 0, 0);*/

	
    //zeGraphics->SetHUD(false);
}

void SceneB::Exit()
{
	/*delete Devil;
	Devil = nullptr;*/
	for (std::vector<GameEntity*>::iterator it = m_GoList.begin(), end = m_GoList.end(); it != end; ++it)
	{
		delete *it;
		*it = nullptr;
	}
	m_GoList.clear();
	m_ally.clear();
	m_enemy.clear();
}

