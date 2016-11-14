#include "NPCBuilder.h"
#include "../Gathering of Components/HPandDPComponent.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Gathering of Components/SpeedComponent.h"
#include "../Gathering of Components/MeshComponent.h"
#include "../Systems/Scene_System.h"
#include "../Scenes/GraphicsEntity.h"
#include "../StatesStuff/StateMachineComponent.h"
#include "../Gathering of Components/AllyEnemyComponent.h"
#include "../StatesStuff/IdleState.h"
#include "../StatesStuff/PatrolState.h"
#include "../StatesStuff/GoThereState.h"
#include "../StatesStuff/DogBarkState.h"

GameEntity *NPCBuilder::BuildZombie(const std::string &zeName, Vector3 &boundary, std::vector<GameEntity*> &enemyList, std::vector<GameEntity*> &allyList, const Vector3 &zePos)
{
    GameEntity *go = new GameEntity;
    go->setName(zeName);
    enemyList.push_back(go);

    MeshComponent *zeMesh = new MeshComponent();
    GraphicsEntity *zeGraphics = dynamic_cast<GraphicsEntity*>(&Scene_System::accessing().getGraphicsScene());
    zeMesh->onNotify(zeGraphics->getMeshID("greenQuad"));
    go->addComponent(MeshComponent::g_CompID_.getValue(), zeMesh);

    PhysicsComponent *zePhysics = new PhysicsComponent();
    zePhysics->setPos(zePos);
    zePhysics->setSize(Vector3(25, 25, 1));
    zePhysics->setBoundary(boundary);
    go->addComponent(PhysicsComponent::g_ID_, zePhysics);

    StateMachineComponent *zeFSM = new StateMachineComponent;
    go->addComponent(StateMachineComponent::ID_.getValue(), zeFSM);
    zeFSM->addStates(*new IdleState, IdleState::ID_);
    zeFSM->addStates(*new GoThereState, GoThereState::ID_);

    AllyEnemyComponent *toRecogniseEnemyAlly = new AllyEnemyComponent;
    toRecogniseEnemyAlly->setAllyList(enemyList).setEnemyList(allyList);
    go->addComponent(AllyEnemyComponent::ID_, toRecogniseEnemyAlly);

    return go;
}
GameEntity *NPCBuilder::BuildDog(const std::string &zeName, Vector3 &boundary, std::vector<GameEntity*> &enemyList, std::vector<GameEntity*> &allyList, const Vector3 &zePos)
{
    GameEntity *go = new GameEntity;
    go->setName(zeName);
    allyList.push_back(go);

    MeshComponent *zeMesh = new MeshComponent();
    GraphicsEntity *zeGraphics = dynamic_cast<GraphicsEntity*>(&Scene_System::accessing().getGraphicsScene());
    zeMesh->onNotify(zeGraphics->getMeshID("whiteQuad"));
    go->addComponent(MeshComponent::g_CompID_.getValue(), zeMesh);

    PhysicsComponent *zePhysics = new PhysicsComponent();
    zePhysics->setPos(zePos);
    zePhysics->setSize(Vector3(20, 20, 1));
    zePhysics->setBoundary(boundary);
    go->addComponent(PhysicsComponent::g_ID_, zePhysics);

    StateMachineComponent *zeFSM = new StateMachineComponent;
    go->addComponent(StateMachineComponent::ID_.getValue(), zeFSM);
    zeFSM->addStates(*new PatrolState, PatrolState::ID_);
    zeFSM->addStates(*new DogBarkState, DogBarkState::ID_);
    zeFSM->getSpecificStates(PatrolState::ID_).onNotify(50.f);

    AllyEnemyComponent *toRecogniseEnemyAlly = new AllyEnemyComponent;
    toRecogniseEnemyAlly->setAllyList(allyList).setEnemyList(enemyList);
    go->addComponent(AllyEnemyComponent::ID_, toRecogniseEnemyAlly);

    return go;
}
