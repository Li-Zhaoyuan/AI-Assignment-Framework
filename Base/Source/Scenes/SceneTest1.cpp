#include "SceneTest1.h"
#include "../Systems/Scene_System.h"
#include "GraphicsEntity.h"
#include <sstream>
#include "../Misc/NPCBuilder.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../Gathering of Components/HPandDPComponent.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Gathering of Components/MeshComponent.h"
#include "../Misc/GlobalFunctions.h"
#include "../Systems/MessageSystem.h"

#define MAX_LIMIT_DISPLAY_MESSAGE 4

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

	// The very reason why we can't see any thing
	Mtx44 ortho;
	ortho.SetToOrtho(-320, 320, -180, 180, -100, 100);
	projectionStack->LoadMatrix(ortho);
	// The very reason why we can't see any thing
	boundaryOfRoom.Set(320, 180, 0);
	// The very reason why we can't see any thing
	healthBarID = zeGraphics->getMeshID("redCube");
	background = zeGraphics->getMeshID("SceneTestBackground");
    spawnLimitOfDog = 2;
    zombiePresence = spawnLimitOfZombie = 2;
    for (size_t num = 0, zombiePresence = 0; num < spawnLimitOfZombie; ++num, ++zombiePresence)
        m_GoList.push_back(NPCBuilder::BuildZombie("Zombie", boundaryOfRoom, m_enemy, m_ally, Vector3(Math::RandFloatMinMax(-boundaryOfRoom.x, boundaryOfRoom.x), Math::RandFloatMinMax(-boundaryOfRoom.y, boundaryOfRoom.y), 0)));
	m_GoList.push_back(NPCBuilder::BuildDog("Dog", boundaryOfRoom, m_enemy, m_ally, Vector3(0, 20, 0)));
    m_GoList.push_back(NPCBuilder::BuildDog("Dog", boundaryOfRoom, m_enemy, m_ally, Vector3(Math::RandFloatMinMax(-boundaryOfRoom.x, boundaryOfRoom.x), Math::RandFloatMinMax(-boundaryOfRoom.y, boundaryOfRoom.y), 0)));
    dogPresence = 2;

	m_GoList.push_back(NPCBuilder::BuildDevil("Devil", boundaryOfRoom, m_enemy, m_ally, Vector3(Math::RandFloatMinMax(-boundaryOfRoom.x, boundaryOfRoom.x), Math::RandFloatMinMax(-boundaryOfRoom.y, boundaryOfRoom.y), 0)));
	m_GoList.push_back(NPCBuilder::BuildGuy("Guy", boundaryOfRoom, m_enemy, m_ally, Vector3(Math::RandFloatMinMax(-boundaryOfRoom.x, boundaryOfRoom.x), Math::RandFloatMinMax(-boundaryOfRoom.y, boundaryOfRoom.y), 0)));
    m_GoList.push_back(NPCBuilder::BuildDevil("Devil", boundaryOfRoom, m_enemy, m_ally, Vector3(Math::RandFloatMinMax(-boundaryOfRoom.x, boundaryOfRoom.x), Math::RandFloatMinMax(-boundaryOfRoom.y, boundaryOfRoom.y), 0)));
    m_GoList.push_back(NPCBuilder::BuildGuy("Guy", boundaryOfRoom, m_enemy, m_ally, Vector3(Math::RandFloatMinMax(-boundaryOfRoom.x, boundaryOfRoom.x), Math::RandFloatMinMax(-boundaryOfRoom.y, boundaryOfRoom.y), 0)));
    for (int i = 0; i < 10; ++i)
	{
		nonActiveBulletList.push_back(NPCBuilder::BuildBullet("Bullet", boundaryOfRoom, m_enemy, m_ally, listToDespawn, Vector3(Math::RandFloatMinMax(-boundaryOfRoom.x, boundaryOfRoom.x), Math::RandFloatMinMax(-boundaryOfRoom.y, boundaryOfRoom.y), 0)));
	}
}

void SceneTest1::Update(float dt)
{
#ifdef _DEBUG
    // TODO: Remove it when it is not debugging
    GraphicsEntity *zeGraphics = dynamic_cast<GraphicsEntity*>(&Scene_System::accessing().getGraphicsScene());
    zeGraphics->Update(dt);
    // TODO: Remove it when it is not debugging
#endif
    if (MessageSystem::accessing().getMessage() != "")
    {
        for (std::vector<GameEntity*>::iterator it = m_GoList.begin(), end = m_GoList.end(); it != end; ++it)
        {
            if ((*it)->seeComponentActive(9))   // Only Component with ID of 9 will receive the message from MessageBoard!!!!
                (*it)->getComponent(9).onNotify(MessageSystem::accessing().getMessage());
        }
        MessageSystem::accessing().Update(dt);
    }
    fps = 1 / dt;

	for (std::vector<GameEntity*>::iterator it = m_GoList.begin(), end = m_GoList.end(); it != end; ++it)
	{
		(*it)->Update(dt);
	}
	switch (inactiveObjPos.empty())
	{
	case false:
		for (std::set<size_t>::iterator it = inactiveObjPos.begin(), end = inactiveObjPos.end(); it != end; ++it)
		{
			GameEntity *zeRemovedGo = m_GoList[(*it)];
			m_GoList.erase(m_GoList.end() - (m_GoList.size() - (*it)));
			m_InactiveList.push_back(zeRemovedGo);
            if (checkWhetherTheWordInThatString("Dog", zeRemovedGo->getName()))
            {
                --dogPresence;
                SpawnDog(Vector3(Math::RandFloatMinMax(-boundaryOfRoom.x, boundaryOfRoom.x), Math::RandFloatMinMax(-boundaryOfRoom.y, boundaryOfRoom.y), 0));
            }
            else if (checkWhetherTheWordInThatString("Zombie", zeRemovedGo->getName()))
            {
                --zombiePresence;
                SpawnZombie(Vector3(Math::RandFloatMinMax(-boundaryOfRoom.x, boundaryOfRoom.x), Math::RandFloatMinMax(-boundaryOfRoom.y, boundaryOfRoom.y), 0));
            }
		}
		inactiveObjPos.clear();
		break;
	default:
		break;
	}
	switch (tempStorage.empty())
	{
	case false:
		while (tempStorage.empty() == false)
		{
			GameEntity *zeGo = tempStorage.back();
			tempStorage.pop_back();
			m_GoList.push_back(zeGo);
		}
		break;
	default:
		break;
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
}

void SceneTest1::Render()
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
	modelStack->Scale(boundaryOfRoom.x * 2, boundaryOfRoom.x * 2, 1);
	zeGraphics->RenderMesh(background, false);
	modelStack->PopMatrix();

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
			HPandDPComponent *zeHP = dynamic_cast<HPandDPComponent*>(&(*it)->getComponent(HPandDPComponent::ID_));
			if ((*it)->seeComponentActive(7))
				zeGraphics->getMeshRef(zeMeshID->getMeshID()).onNotify((*it)->getComponent(7));
			//MyMeshComponent *zeMesh = dynamic_cast<MyMeshComponent*>(&(*it)->getComponent(MyMeshComponent::ID_));
			modelStack->Translate(zePhysicsStuff->getPos().x, zePhysicsStuff->getPos().y, zePhysicsStuff->getPos().z);
			// Debuggin Stuff
			modelStack->PushMatrix();
			modelStack->Translate(0, (zePhysicsStuff->getSize().y / 2) + 5.f, 0);
			modelStack->Scale(15, 15, 1);
			zeGraphics->RenderText((*it)->getName(), Color(1, 0, 0));
			modelStack->PopMatrix();

			if (zeHP->getHealth() > 0) {
				modelStack->PushMatrix();
				modelStack->Translate(0, (-zePhysicsStuff->getSize().y / 2) - 5.f, 0);
				modelStack->Scale(zeHP->getHealth() / 2.5f, 5, 1);
				//ss.str("");
				//ss << zeHP->getHealth();
				zeGraphics->RenderMesh(healthBarID, false);
				modelStack->PopMatrix();
			}
			// Debuggin Stuff
			modelStack->Scale(zePhysicsStuff->getSize().x, zePhysicsStuff->getSize().y, 1);
			zeGraphics->RenderMesh(zeMeshID->getMeshID(), false);
			//zeGraphics->RenderMesh(*zeMesh, false);
			modelStack->PopMatrix();
		}
		break;
		default:
			break;
		}
	}

    zeGraphics->SetHUD(true);
    viewStack->LoadIdentity();
    std::ostringstream ss;
    ss << "FPS:" << fps;
    zeGraphics->RenderTextOnScreen(ss.str(), Color(0, 1, 0), 25, 0, 0);

    // Starting from the latest Message thus getting the size of stored message and num starts from size - 5 to get the last 4th element of the message array then increment
    zeGraphics->RenderTextOnScreen("Text|From|To", Color(1, 0, 0), 25, 0, 550);
    for (int sizeOfMessage = MessageSystem::accessing().StoreMessage.size(), num = sizeOfMessage - MAX_LIMIT_DISPLAY_MESSAGE; num < sizeOfMessage; ++num)
    {
        if (num < 0)    // Vector will went out of range if it is less than 0!
            continue;
        size_t posOfLastOr = MessageSystem::accessing().StoreMessage[num].find_last_of("|");    // this will find '|' from end to beginning
        //size_t posOfFirstOr = MessageSystem::accessing().StoreMessage[num].find("|");
        //size_t posOfLastOr = MessageSystem::accessing().StoreMessage[num].find("|", posOfFirstOr); // Finding the second '|'
        std::string extractedText = MessageSystem::accessing().StoreMessage[num].substr(0, posOfLastOr);    // Get the extracted text out of the overall message
        zeGraphics->RenderTextOnScreen(extractedText, Color(1, 0, 0), 25, 0,
            525.0f - (25.0f*(sizeOfMessage - 1.0f - num))); // 525 is from above 550 - 25. 25 shall be the constant size for the text. Then the minus operation after 525 will help to get the the actual values we want.
        // Example: sizeOfMessage = 4. num = 0. overall = 0.
    }
    zeGraphics->SetHUD(false);
}

void SceneTest1::Exit()
{
	for (std::vector<GameEntity*>::iterator it = m_GoList.begin(), end = m_GoList.end(); it != end; ++it)
	{
		delete *it;
		*it = nullptr;
	}
	m_GoList.clear();
	m_ally.clear();
	m_enemy.clear();
	for (std::vector<GameEntity*>::iterator it = m_InactiveList.begin(), end = m_InactiveList.end(); it != end; ++it)
	{
		delete *it;
		*it = nullptr;
	}
	m_InactiveList.clear();
	for (std::vector<GameEntity*>::iterator it = nonActiveBulletList.begin(), end = nonActiveBulletList.end(); it != end; ++it)
	{
		delete *it;
		*it = nullptr;
	}
	nonActiveBulletList.clear();
	for (std::vector<GameEntity*>::iterator it = listToDespawn.begin(), end = listToDespawn.end(); it != end; ++it)
	{
		delete *it;
		*it = nullptr;
	}
	listToDespawn.clear();
	for (auto it : tempStorage)
	{
		delete it;
		it = nullptr;
	}
	tempStorage.clear();

	inactiveObjPos.clear();
}

bool SceneTest1::onNotify(GenericEntity &zeEvent)
{
	for (std::vector<GameEntity*>::iterator it = m_GoList.begin(), end = m_GoList.end(); it != end; ++it)
	{
		if ((*it)->getName() == zeEvent.getName())
		{
			inactiveObjPos.insert(it - m_GoList.begin());
			AllyEnemyComponent *zeAlly = dynamic_cast<AllyEnemyComponent*>(&(*it)->getComponent(AllyEnemyComponent::ID_));
			for (std::vector<GameEntity*>::iterator it2 = zeAlly->m_allyList->begin(), end2 = zeAlly->m_allyList->end(); it2 != end2; ++it2)
			{
				if ((*it2)->getName() == zeEvent.getName())
				{
					zeAlly->m_allyList->erase(it2);
					break;
				}
			}
			break;
		}
	}
	return true;
}

bool SceneTest1::onNotify(const std::string &zeEvent)
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
		bullet = NPCBuilder::BuildBullet("Bullet", boundaryOfRoom, m_enemy, m_ally, listToDespawn, Vector3(Math::RandFloatMinMax(-boundaryOfRoom.x, boundaryOfRoom.x), Math::RandFloatMinMax(-boundaryOfRoom.y, boundaryOfRoom.y), 0));
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

bool SceneTest1::SpawnDog(const Vector3 &zePos)
{
    if (dogPresence < spawnLimitOfDog)
    {
        for (std::vector<GameEntity*>::iterator it = m_InactiveList.begin(), end = m_InactiveList.end(); it != end; ++it)
        {
            if (checkWhetherTheWordInThatString("Dog", (*it)->getName()))
            {
                (*it)->getComponent(HPandDPComponent::ID_).Exit();
                (*it)->getComponent(1).Exit();
                PhysicsComponent *zePhysicz = dynamic_cast<PhysicsComponent*>(&(*it)->getComponent(PhysicsComponent::g_ID_));
                zePhysicz->Exit();
                zePhysicz->setPos(zePos);
                GameEntity *zeDog = (*it);
                m_InactiveList.erase(it);
                tempStorage.push_back(zeDog);
                m_ally.push_back(zeDog);
                ++dogPresence;
                return true;
                break;
            }
        }
        tempStorage.push_back(NPCBuilder::BuildDog("Dog", boundaryOfRoom, m_enemy, m_ally, zePos));
        ++dogPresence;
        return true;
    }
    return false;
}

bool SceneTest1::SpawnZombie(const Vector3 &zePos)
{
    if (zombiePresence < spawnLimitOfZombie)
    {
        for (std::vector<GameEntity*>::iterator it = m_InactiveList.begin(), end = m_InactiveList.end(); it != end; ++it)
        {
            if (checkWhetherTheWordInThatString("Zombie", (*it)->getName()))
            {
                (*it)->getComponent(HPandDPComponent::ID_).Exit();
                (*it)->getComponent(1).Exit();
                PhysicsComponent *zePhysicz = dynamic_cast<PhysicsComponent*>(&(*it)->getComponent(PhysicsComponent::g_ID_));
                zePhysicz->Exit();
                zePhysicz->setPos(zePos);
                m_enemy.push_back(*it);
                tempStorage.push_back(*it);
                m_InactiveList.erase(it);
                ++zombiePresence;
                return true;
                break;
            }
        }
        tempStorage.push_back(NPCBuilder::BuildZombie("Zombie", boundaryOfRoom, m_enemy, m_ally, zePos));
        ++zombiePresence;
        return true;
    }
    return false;
}