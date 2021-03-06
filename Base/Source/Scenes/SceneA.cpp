#include "SceneA.h"
#include "../Systems/Scene_System.h"
#include "GraphicsEntity.h"
#include <sstream>
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Gathering of Components/MeshComponent.h"
#include "../Gathering of Components/HPandDPComponent.h"
//TODO: Be Removed
//#include "../StatesStuff/StateMachineComponent.h"
//#include "../StatesStuff/IdleState.h"   
//TODO: Be Removed
#include "../Misc/NPCBuilder.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../Misc/GlobalFunctions.h"

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

    ////Calculating aspect ratio
    //m_worldHeight = 100.f;
    //m_worldWidth = m_worldHeight * ((float)Application::GetInstance().cA_WindowWidth / Application::GetInstance().cA_WindowHeight);
    fps = 1;
    zeGraphics->m_renderPass = GraphicsEntity::RENDER_PASS_MAIN;

    // The very reason why we can't see any thing
    Mtx44 ortho;
    ortho.SetToOrtho(-320, 320, -180, 180, -100, 100);
    projectionStack->LoadMatrix(ortho);
    // The very reason why we can't see any thing
    boundaryOfRoom.Set(320, 180, 0);
    //Calculating aspect ratio
    m_worldHeight = boundaryOfRoom.y * 2;
    m_worldWidth = m_worldHeight * ((float)Application::GetInstance().cA_WindowWidth / Application::GetInstance().cA_WindowHeight);

    m_GoList.push_back(NPCBuilder::BuildZombie("Zombie", boundaryOfRoom, m_enemy, m_ally, Vector3(-55, 0, 0)));
    m_GoList.push_back(NPCBuilder::BuildDog("Dog", boundaryOfRoom, m_enemy, m_ally, Vector3(0,20,0)));
    //m_GoList.push_back(NPCBuilder::BuildZombie("Zombie", boundaryOfRoom, m_enemy, m_ally, Vector3(140,100, 0)));
    //m_GoList.push_back(NPCBuilder::BuildZombie("Zombie", boundaryOfRoom, m_enemy, m_ally, Vector3(140, -150, 0)));
    m_GoList.push_back(NPCBuilder::BuildDog("Dog", boundaryOfRoom, m_enemy, m_ally, Vector3(-200, 20, 0)));

#ifdef _DEBUG
    TestingOutSprite = new GameEntity;
    MeshComponent *zeSpriteComp = new MeshComponent;
    zeSpriteComp->onNotify(zeGraphics->getMeshID("DogSprite"));
    TestingOutSprite->addComponent(MeshComponent::g_CompID_.getValue(), zeSpriteComp);
    AnimationComponent *zeAnim = new AnimationComponent;
    zeAnim->Set(0, 8, 20, 0.5, true);
    TestingOutSprite->addComponent(AnimationComponent::ID_, zeAnim);

#endif
    mouseXinGameScreen = 0;
    mouseYinGameScreen = 0;
    zeBackground = zeGraphics->getMeshID("SceneA");
    healthBarID = zeGraphics->getMeshID("redCube");
}

void SceneA::Update(float dt)
{
#ifdef _DEBUG
    // TODO: Remove it when it is not debugging
    GraphicsEntity *zeGraphics = dynamic_cast<GraphicsEntity*>(&Scene_System::accessing().getGraphicsScene());
    zeGraphics->Update(dt);
    //TestingOutSprite->Update(dt);
    // TODO: Remove it when it is not debugging
    double mouseX, mouseY;
    Application::GetCursorPos(&mouseX, &mouseY);
    int gameWidth = Application::GetInstance().cA_WindowWidth;
    int gameH = Application::GetInstance().cA_WindowHeight;
    mouseXinGameScreen = ((float)mouseX / gameWidth * m_worldWidth) - (boundaryOfRoom.x );
    mouseYinGameScreen = ((float)(gameH - mouseY) / gameH * m_worldHeight) - (boundaryOfRoom.y);
#endif
    fps = 1 / dt;
    if (Application::IsKeyPressed(VK_NUMPAD2))
        Scene_System::accessing().SwitchScene("B");

    static bool bLButtonState = false;
    if (!bLButtonState && Application::IsMousePressed(0))
    {
        //double mouseX, mouseY;
        //Application::GetCursorPos(&mouseX, &mouseY);
        bLButtonState = true;
        //int gameWidth = Application::GetInstance().cA_WindowWidth;
        //int gameH = Application::GetInstance().cA_WindowHeight;
        //mouseXinGameScreen = ((float)mouseX / gameWidth * m_worldWidth) - (boundaryOfRoom.x);
        //mouseYinGameScreen = ((float)(gameH - mouseY) / gameH * m_worldHeight) - (boundaryOfRoom.y);
        SpawnDog(Vector3((float)mouseXinGameScreen, (float)mouseYinGameScreen, 0));
        //std::cout << "LBUTTON DOWN" << std::endl;
    }
    else if (bLButtonState && !Application::IsMousePressed(0))
    {
        bLButtonState = false;
        //std::cout << "LBUTTON UP" << std::endl;
    }
    static bool bRButtonState = false;
    if (!bRButtonState && Application::IsMousePressed(1))
    {
        //double mouseX, mouseY;
        //Application::GetCursorPos(&mouseX, &mouseY);
        bRButtonState = true;
        //int gameWidth = Application::GetInstance().cA_WindowWidth;
        //int gameH = Application::GetInstance().cA_WindowHeight;
        //mouseXinGameScreen = ((float)mouseX / gameWidth * m_worldWidth) - (boundaryOfRoom.x);
        //mouseYinGameScreen = ((float)(gameH - mouseY) / gameH * m_worldHeight) - (boundaryOfRoom.y);
        SpawnZombie(Vector3((float)mouseXinGameScreen, (float)mouseYinGameScreen, 0));
        //std::cout << "RBUTTON DOWN" << std::endl;
    }
    else if (bRButtonState && !Application::IsMousePressed(1))
    {
        bRButtonState = false;
        //std::cout << "RBUTTON UP" << std::endl;
    }

    for (std::vector<GameEntity*>::iterator it = m_GoList.begin(), end = m_GoList.end(); it != end; ++it)
    {
        (*it)->Update(dt);
    }

    switch (inactiveObjPos.empty())
    {
    case false:
        for (std::vector<size_t>::iterator it = inactiveObjPos.begin(), end = inactiveObjPos.end(); it != end; ++it)
        {
            GameEntity *zeRemovedGo = m_GoList[(*it)];
            m_GoList.erase(m_GoList.end() - (m_GoList.size() - (*it)));
            m_InactiveList.push_back(zeRemovedGo);
        }
        inactiveObjPos.clear();
        break;
    default:
        break;
    }
    switch (activeObjPos.empty())
    {
    case false:
        for (std::vector<size_t>::iterator it = activeObjPos.begin(), end = activeObjPos.end(); it != end; ++it)
        {
            GameEntity *zeRemovedGo = m_InactiveList[(*it)];
            m_InactiveList.erase(m_InactiveList.end() - (m_InactiveList.size() - (*it)));
            m_GoList.push_back(zeRemovedGo);
        }
        activeObjPos.clear();
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

#ifdef _DEBUG
    //MeshComponent *zeSprite = dynamic_cast<MeshComponent*>(&TestingOutSprite->getComponent(MeshComponent::g_CompID_.getValue()));
    //zeGraphics->getMeshRef(zeSprite->getMeshID()).onNotify(TestingOutSprite->getComponent(AnimationComponent::ID_));
    //modelStack->PushMatrix();
    //modelStack->Scale(50, 50, 1);
    //zeGraphics->RenderMesh(dynamic_cast<MeshComponent*>(&TestingOutSprite->getComponent(MeshComponent::g_CompID_.getValue()))->getMeshID(), false);
    //modelStack->PopMatrix();
#endif
    modelStack->PushMatrix();
    modelStack->Translate(0, 0, -5);
    modelStack->Scale(boundaryOfRoom.x * 2.f, boundaryOfRoom.y*2.f, 1);
    zeGraphics->RenderMesh(zeBackground, false);
    modelStack->PopMatrix();
    std::ostringstream ss;
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
                    modelStack->Scale(zeHP->getHealth()/2.5f, 10, 1);
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

    //zeGraphics->SetHUD(true);
    viewStack->LoadIdentity();
    //std::ostringstream ss;
    ss.str("");
    ss << "FPS:" << fps;
    zeGraphics->RenderTextOnScreen(ss.str(), Color(0, 1, 0), 15, -boundaryOfRoom.x, -boundaryOfRoom.y);

#ifdef _DEBUG
    ss.str("");
    ss << mouseXinGameScreen << ":" << mouseYinGameScreen;
    zeGraphics->RenderTextOnScreen(ss.str(), Color(0, 1, 0), 15, -boundaryOfRoom.x, -boundaryOfRoom.y+ 15);
#endif
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
    for (std::vector<GameEntity*>::iterator it = m_InactiveList.begin(), end = m_InactiveList.end(); it != end; ++it)
    {
        delete *it;
        *it = nullptr;
    }
    m_InactiveList.clear();
    for (auto it : tempStorage)
    {
        delete it;
        it = nullptr;
    }
    tempStorage.clear();

    activeObjPos.clear();
    inactiveObjPos.clear();

#ifdef _DEBUG
    delete TestingOutSprite;
#endif
}

bool SceneA::onNotify(GenericEntity &zeEvent)
{
    for (std::vector<GameEntity*>::iterator it = m_GoList.begin(), end = m_GoList.end(); it != end; ++it)
    {
        if ((*it)->getName() == zeEvent.getName())
        {
            inactiveObjPos.push_back(it - m_GoList.begin());
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

bool SceneA::SpawnDog(const Vector3 &zePos)
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
            return true;
            break;
        }   
    }
    tempStorage.push_back(NPCBuilder::BuildDog("Dog", boundaryOfRoom, m_enemy, m_ally, zePos));
    return true;
}

bool SceneA::SpawnZombie(const Vector3 &zePos)
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
            return true;
            break;
        }
    }
    tempStorage.push_back(NPCBuilder::BuildZombie("Zombie", boundaryOfRoom, m_enemy, m_ally, zePos));
    return true;
}