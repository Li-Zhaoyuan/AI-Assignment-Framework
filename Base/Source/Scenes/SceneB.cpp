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
#include "../StatesStuff/Devil_HealState.h"
#include "../StatesStuff/Devil_EscapeState.h"  
#include "../StatesStuff/Guy_PatrolState.h"   
#include "../StatesStuff/Guy_EscapeState.h"   
#include "../StatesStuff/Guy_StunState.h"
#include "../StatesStuff/Guy_AttackState.h"
#include "../Gathering of Components/HPandDPComponent.h"
#include "../Gathering of Components/CollisionComponent.h"
#include "../Gathering of Components/DevilAnimComponent.h"
#include "../Gathering of Components/GuyAnimComponent.h"
#include "../Misc/GlobalFunctions.h"


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
	devilMesh->onNotify(zeGraphics->getMeshID("DevilSprite"));
	Devil->addComponent(MeshComponent::g_CompID_.getValue(), devilMesh);
	PhysicsComponent *devilPhysic = new PhysicsComponent();
	devilPhysic->setSize(Vector3(30, 30, 1));
	devilPhysic->setYrotation(0);
	devilPhysic->setBoundary(boundary);
	devilPhysic->setPos(Vector3(0, 0, 0));
	Devil->addComponent(PhysicsComponent::g_ID_, devilPhysic);
	
	StateMachineComponent *devilFSM = new StateMachineComponent();
	Devil->addComponent(StateMachineComponent::ID_.getValue(), devilFSM);
	devilFSM->addStates(*new Devil_SearchState(), Devil_SearchState::ID_);
	devilFSM->addStates(*new Devil_AttackState(), Devil_AttackState::ID_);
	devilFSM->addStates(*new Devil_EscapeState(), Devil_EscapeState::ID_);
	devilFSM->addStates(*new Devil_HealState(), Devil_HealState::ID_);
	Devil->addComponent(HPandDPComponent::ID_, new HPandDPComponent(100, 15));

	AllyEnemyComponent *DeviltoRecogniseEnemyAlly = new AllyEnemyComponent();
	DeviltoRecogniseEnemyAlly->setAllyList(m_enemy).setEnemyList(m_ally);
	Devil->addComponent(AllyEnemyComponent::ID_, DeviltoRecogniseEnemyAlly);
	Devil->addComponent(DevilAnimComp::ID_, new DevilAnimComp());

	m_GoList.push_back(Devil);
	m_enemy.push_back(Devil);

	GameEntity *Guy = new GameEntity();
	Guy->setName("Guy");
	MeshComponent *guyMesh = new MeshComponent();
	guyMesh->onNotify(zeGraphics->getMeshID("GuySprite"));
	Guy->addComponent(MeshComponent::g_CompID_.getValue(), guyMesh);
	PhysicsComponent *guyPhysic = new PhysicsComponent();
	guyPhysic->setSize(Vector3(20, 20, 1));
	guyPhysic->setYrotation(0);
	guyPhysic->setBoundary(boundary);
	guyPhysic->setPos(Vector3(150, 0, 0));
	Guy->addComponent(PhysicsComponent::g_ID_, guyPhysic);

	StateMachineComponent *guyFSM = new StateMachineComponent();
	Guy->addComponent(StateMachineComponent::ID_.getValue(), guyFSM);
	guyFSM->addStates(*new Guy_PatrolState(), Guy_PatrolState::ID_);
	guyFSM->addStates(*new Guy_EscapeState(), Guy_EscapeState::ID_);
	guyFSM->addStates(*new Guy_StunState(), Guy_StunState::ID_);
	guyFSM->addStates(*new Guy_AttackState(), Guy_AttackState::ID_);
	Guy->addComponent(HPandDPComponent::ID_, new HPandDPComponent(100, 15));
	
	AllyEnemyComponent *GuytoRecogniseEnemyAlly = new AllyEnemyComponent;
	GuytoRecogniseEnemyAlly->setAllyList(m_ally).setEnemyList(m_enemy);
	Guy->addComponent(AllyEnemyComponent::ID_, GuytoRecogniseEnemyAlly);
	Guy->addComponent(GuyAnimComp::ID_, new GuyAnimComp());

	m_GoList.push_back(Guy);
	m_ally.push_back(Guy);

	/*healthBars = new GameEntity();
	healthBars->setName("healthBars");
	MeshComponent *healthBarMesh = new MeshComponent();
	healthBarMesh->onNotify(zeGraphics->getMeshID("redCube"));
	healthBars->addComponent(MeshComponent::g_CompID_.getValue(), healthBarMesh);
	PhysicsComponent *healthBarPhysic = new PhysicsComponent();
	healthBarPhysic->setSize(Vector3(1, 5, 1));
	healthBarPhysic->setYrotation(0);
	healthBarPhysic->setBoundary(boundary);
	healthBarPhysic->setPos(Vector3(150, 0, 0));
	healthBars->addComponent(PhysicsComponent::g_ID_, healthBarPhysic);*/

	for (int i = 0; i < 10; ++i)
	{
		GameEntity* bullet = new GameEntity();
		bullet->setName("Bullet");
		MeshComponent *bulletMesh = new MeshComponent();
		bulletMesh->onNotify(zeGraphics->getMeshID("bullet"));
		bullet->addComponent(MeshComponent::g_CompID_.getValue(), bulletMesh);
		PhysicsComponent *bulletPhysic = new PhysicsComponent();
		bulletPhysic->setSize(Vector3(5, 5, 1));
		bulletPhysic->setYrotation(0);
		bulletPhysic->setBoundary(boundary);
		bulletPhysic->setPos(Vector3(150, 0, 0));
		bullet->addComponent(PhysicsComponent::g_ID_, bulletPhysic);
		AllyEnemyComponent *bullettoRecogniseEnemyAlly = new AllyEnemyComponent;
		//GuytoRecogniseEnemyAlly->setAllyList(m_ally).setEnemyList(m_enemy);
		bullet->addComponent(AllyEnemyComponent::ID_, bullettoRecogniseEnemyAlly);
		bullet->addComponent(HPandDPComponent::ID_, new HPandDPComponent(100, 25));
		CollisionComponent *bulletCollision = new CollisionComponent;
		bulletCollision->setDespawnList(listToDespawn).setEnemyList(m_enemy);
		bullet->addComponent(CollisionComponent::ID_, bulletCollision);

		nonActiveBulletList.push_back(bullet);
	}
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
	//onNotify("hi");
	if (!tempStorage.empty())
	{
		m_GoList.push_back(tempStorage.back());
		tempStorage.pop_back();
	}
	while (!listToDespawn.empty())
	{
		GameEntity* despawn;
		despawn = listToDespawn.back();
		//int i = 0;
		for (std::vector<GameEntity*>::iterator it = m_GoList.begin(), end = m_GoList.end(); it != end; ++it)
		{
			if (despawn == (*it))
			{
				listToDespawn.pop_back();
				m_GoList.erase(it);
				break;
			}
		}
		/*for (std::vector<GameEntity*>::iterator it = despawningBullets.begin(), end = despawningBullets.end(); it != end; ++it)
		{
			for (std::vector<GameEntity*>::iterator it2 = m_GoList.begin(), end = m_GoList.end(); it2 != end; ++it2)
			{
				if ((*it) == (*it2))
				{

				}
			}
		}*/
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
	//PhysicsComponent *zePhysicsStuffForHealth = dynamic_cast<PhysicsComponent*>(&(healthBars)->getComponent(PhysicsComponent::g_ID_));
	//MeshComponent *zeMeshIDForHealth = dynamic_cast<MeshComponent*>(&(healthBars)->getComponent(MeshComponent::g_CompID_.getValue()));

	for (std::vector<GameEntity*>::iterator it = m_GoList.begin(), end = m_GoList.end(); it != end; ++it)
	{
		PhysicsComponent *zePhysicsStuff = dynamic_cast<PhysicsComponent*>(&(*it)->getComponent(PhysicsComponent::g_ID_));
		MeshComponent *zeMeshID = dynamic_cast<MeshComponent*>(&(*it)->getComponent(MeshComponent::g_CompID_.getValue()));
		
		switch ((*it)->seeComponentActive(MeshComponent::g_CompID_.getValue()))
		{
		case true:
		{
					 if (!checkWhetherTheWordInThatString("Bullet", (*it)->getName()))
					 {
						 modelStack->PushMatrix();
						 HPandDPComponent*zeHP = dynamic_cast<HPandDPComponent*>(&(*it)->getComponent(HPandDPComponent::ID_));
						 if ((*it)->seeComponentActive(7))
							 zeGraphics->getMeshRef(zeMeshID->getMeshID()).onNotify((*it)->getComponent(7));
						 modelStack->Translate(zePhysicsStuff->getPos().x, zePhysicsStuff->getPos().y, zePhysicsStuff->getPos().z);
						 // Debuggin Stuff
						 modelStack->PushMatrix();
						 modelStack->Translate(-25, (zePhysicsStuff->getSize().y / 2) + 5.f, 0);
						 modelStack->Scale(10, 10, 1);
						 zeGraphics->RenderText((*it)->getName(), Color(1, 0, 0));
						 modelStack->PopMatrix();

						 if (zeHP->getHealth() > 0)
						 {
							 modelStack->PushMatrix();
							 modelStack->Translate(0, -(zePhysicsStuff->getSize().y / 2) - 5.f, 0);
							 modelStack->Scale(zeHP->getHealth() / 4.f, 5, 1);
							 zeGraphics->RenderMesh(zeGraphics->getMeshID("redCube"), false);
							 modelStack->PopMatrix();
						 }
						 // Debuggin Stuff
						 modelStack->Scale(zePhysicsStuff->getSize().x, zePhysicsStuff->getSize().y, zePhysicsStuff->getSize().z);
						 zeGraphics->RenderMesh(zeMeshID->getMeshID(), false);
						 modelStack->PopMatrix();
					 }
					 else
					 {
						 modelStack->PushMatrix();
						 modelStack->Translate(zePhysicsStuff->getPos().x, zePhysicsStuff->getPos().y, zePhysicsStuff->getPos().z);
						 // Debuggin Stuff
						
						 // Debuggin Stuff
						 modelStack->Scale(zePhysicsStuff->getSize().x, zePhysicsStuff->getSize().y, zePhysicsStuff->getSize().z);
						 zeGraphics->RenderMesh(zeMeshID->getMeshID(), false);
						 modelStack->PopMatrix();
					 }

					 
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
	Devil = nullptr;
	GameEntity* m_allyBullet, *m_enemyBullet, *healthBars;
	std::vector<GameEntity*> m_GoList, nonActiveBulletList, nonActiveAllyEnemies;
	std::vector<GameEntity*> m_enemy, m_ally;*/
	for (std::vector<GameEntity*>::iterator it = m_GoList.begin(), end = m_GoList.end(); it != end; ++it)
	{
		delete *it;
		*it = nullptr;
	}
	for (std::vector<GameEntity*>::iterator it = nonActiveBulletList.begin(), end = nonActiveBulletList.end(); it != end; ++it)
	{
		delete *it;
		*it = nullptr;
	}
	/*for (std::vector<GameEntity*>::iterator it = nonActiveAllyEnemies.begin(), end = nonActiveAllyEnemies.end(); it != end; ++it)
	{
		delete *it;
		*it = nullptr;
	}*/
	
	nonActiveBulletList.clear();
	//nonActiveAllyEnemies.clear();
	m_GoList.clear();
	m_ally.clear();
	m_enemy.clear();
	listToDespawn.clear();
}

bool SceneB::onNotify(const std::string &zeEvent)
{
	GameEntity* bullet;
	if (!nonActiveBulletList.empty())
	{
		bullet = nonActiveBulletList.back();
		tempStorage.push_back(bullet);
		nonActiveBulletList.pop_back();
	}
	else
	{//create new bullet
		GraphicsEntity *zeGraphics = dynamic_cast<GraphicsEntity*>(&Scene_System::accessing().getGraphicsScene());
		bullet = new GameEntity();
		bullet->setName("Bullet");
		MeshComponent *bulletMesh = new MeshComponent();
		bulletMesh->onNotify(zeGraphics->getMeshID("bullet"));
		bullet->addComponent(MeshComponent::g_CompID_.getValue(), bulletMesh);
		PhysicsComponent *bulletPhysic = new PhysicsComponent();
		bulletPhysic->setSize(Vector3(5, 5, 1));
		bulletPhysic->setYrotation(0);
		bulletPhysic->setBoundary(boundary);
		bulletPhysic->setPos(Vector3(150, 0, 0));
		bullet->addComponent(PhysicsComponent::g_ID_, bulletPhysic);
		AllyEnemyComponent *bullettoRecogniseEnemyAlly = new AllyEnemyComponent();
		//bullettoRecogniseEnemyAlly->setAllyList(m_ally).setEnemyList(m_enemy);
		bullet->addComponent(AllyEnemyComponent::ID_, bullettoRecogniseEnemyAlly);
		bullet->addComponent(HPandDPComponent::ID_, new HPandDPComponent(100, 25));
		CollisionComponent *bulletCollision = new CollisionComponent;
		bulletCollision->setDespawnList(listToDespawn).setEnemyList(m_enemy);
		bullet->addComponent(CollisionComponent::ID_, bulletCollision);

		tempStorage.push_back(bullet);
	}
	//std::string debugddd = "ally/GO:1,2,3/POS:4,5,6";
	//ally/GO:X,Y,Z/POS:X,Y,Z 
	AllyEnemyComponent *bullettoRecogniseEnemyAlly = dynamic_cast<AllyEnemyComponent*>(&bullet->getComponent(AllyEnemyComponent::ID_));
	PhysicsComponent *bulletPhysic = dynamic_cast<PhysicsComponent*>(&bullet->getComponent(PhysicsComponent::g_ID_));
	if (checkWhetherTheWordInThatString("ally", zeEvent))
		bullettoRecogniseEnemyAlly->setAllyList(m_ally).setEnemyList(m_enemy);
	else if (checkWhetherTheWordInThatString("enemy", zeEvent))
		bullettoRecogniseEnemyAlly->setAllyList(m_enemy).setEnemyList(m_ally);
	
	Vector3 tempVel, tempPos;
	
	std::string anotherString = zeEvent.substr(8);
	size_t posOfDelim = anotherString.find(',');

	tempVel.x = stof(anotherString.substr(0, posOfDelim));
	anotherString = anotherString.substr(posOfDelim + 1);
	posOfDelim = anotherString.find(',');
	tempVel.y = stof(anotherString.substr(0, posOfDelim));
	anotherString = anotherString.substr(posOfDelim + 1);
	posOfDelim = anotherString.find('/');
	tempVel.z = stof(anotherString.substr(0, posOfDelim));
	anotherString = anotherString.substr(posOfDelim + 5);
	posOfDelim = anotherString.find(',');
	
	tempPos.x = stof(anotherString.substr(0, posOfDelim));
	anotherString = anotherString.substr(posOfDelim + 1);
	posOfDelim = anotherString.find(',');
	tempPos.y = stof(anotherString.substr(0, posOfDelim));
	anotherString = anotherString.substr(posOfDelim + 1);
	tempPos.z = stof(anotherString);
	bulletPhysic->getPos() = tempPos;
	bulletPhysic->setVel(tempVel);
	//posOfComma = anotherString.find(',');
	return true;
	
	
	//return false;
}