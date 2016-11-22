#include "SceneB.h"
#include "../Systems/Scene_System.h"
#include "GraphicsEntity.h"
#include <sstream>
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Gathering of Components/MeshComponent.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../Gathering of Components/HPandDPComponent.h"
#include "../Misc/NPCBuilder.h"
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
	/*GameEntity *Devil = new GameEntity();
	Devil->setName("Devil");
	MeshComponent *devilMesh = new MeshComponent();
	devilMesh->onNotify(zeGraphics->getMeshID("DevilSprite"));
	Devil->addComponent(MeshComponent::g_CompID_.getValue(), devilMesh);
	PhysicsComponent *devilPhysic = new PhysicsComponent();
	devilPhysic->setSize(Vector3(30, 30, 1));
	devilPhysic->setYrotation(0);
	devilPhysic->setBoundary(boundary);
	devilPhysic->setPos(Vector3(Math::RandFloatMinMax(-boundary.x, boundary.x), Math::RandFloatMinMax(-boundary.y, boundary.y), 0));
	Devil->addComponent(PhysicsComponent::g_ID_, devilPhysic);
	
	StateMachineComponent *devilFSM = new StateMachineComponent();
	Devil->addComponent(StateMachineComponent::ID_.getValue(), devilFSM);
	devilFSM->addStates(*new Devil_SearchState(), Devil_SearchState::ID_);
	devilFSM->addStates(*new Devil_AttackState(), Devil_AttackState::ID_);
	devilFSM->addStates(*new Devil_EscapeState(), Devil_EscapeState::ID_);
	devilFSM->addStates(*new Devil_HealState(), Devil_HealState::ID_);
	Devil->addComponent(HPandDPComponent::ID_, new HPandDPComponent(100, 25));

	AllyEnemyComponent *DeviltoRecogniseEnemyAlly = new AllyEnemyComponent();
	DeviltoRecogniseEnemyAlly->setAllyList(m_enemy).setEnemyList(m_ally);
	Devil->addComponent(AllyEnemyComponent::ID_, DeviltoRecogniseEnemyAlly);
	Devil->addComponent(DevilAnimComp::ID_, new DevilAnimComp());*/

	m_GoList.push_back(NPCBuilder::BuildDevil("Devil", boundary, m_enemy, m_ally, Vector3(Math::RandFloatMinMax(-boundary.x, boundary.x), Math::RandFloatMinMax(-boundary.y, boundary.y), 0)));

	m_GoList.push_back(NPCBuilder::BuildGuy("Guy", boundary, m_enemy, m_ally, Vector3(Math::RandFloatMinMax(-boundary.x, boundary.x), Math::RandFloatMinMax(-boundary.y, boundary.y), 0)));
	//m_ally.push_back(Guy);

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
		

		nonActiveBulletList.push_back(NPCBuilder::BuildBullet("Bullet", boundary, m_enemy, m_ally, listToDespawn, Vector3(Math::RandFloatMinMax(-boundary.x, boundary.x), Math::RandFloatMinMax(-boundary.y, boundary.y), 0)));
	}
	//m_allyBullet, m_enemyBullet;
	background = zeGraphics->getMeshID("sceneBBackground");
	timerForQ = 0.5f;
	timerForW = 0.5f;
	maxDevils = 0;
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
				nonActiveBulletList.push_back(*it);
				m_GoList.erase(it);
				break;
			}
		}
		
	}
	
	timerForW += dt;
	if (timerForW > 15.f && maxDevils <= 10)
	{
		m_GoList.push_back(NPCBuilder::BuildDevil("Devil", boundary, m_enemy, m_ally, Vector3(Math::RandFloatMinMax(-boundary.x, boundary.x), Math::RandFloatMinMax(-boundary.y, boundary.y), 0)));
		if (maxDevils < 3)
			m_GoList.push_back(NPCBuilder::BuildGuy("Guy", boundary, m_enemy, m_ally, Vector3(Math::RandFloatMinMax(-boundary.x, boundary.x), Math::RandFloatMinMax(-boundary.y, boundary.y), 0)));
		timerForW = 0.f;
		maxDevils += 1;
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
		bullet = NPCBuilder::BuildBullet("Bullet", boundary, m_enemy, m_ally, listToDespawn, Vector3(Math::RandFloatMinMax(-boundary.x, boundary.x), Math::RandFloatMinMax(-boundary.y, boundary.y), 0));
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