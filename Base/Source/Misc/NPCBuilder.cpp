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
#include "../StatesStuff/MeleeAttackState.h"
#include <sstream>
#include "../Gathering of Components/SpriteComponent.h"
#include "../StatesStuff/ZombieTarget.h"
#include "../StatesStuff/ZombieCharge.h"
#include "../StatesStuff/DogBite.h"
#include "../Gathering of Components/DogAnimComp.h"
#include "../Gathering of Components/ZombieAnimComp.h"
#include "../StatesStuff/Devil_SearchState.h"   
#include "../StatesStuff/Devil_AttackState.h"   
#include "../StatesStuff/Devil_HealState.h"
#include "../StatesStuff/Devil_EscapeState.h"  
#include "../StatesStuff/Guy_PatrolState.h"   
#include "../StatesStuff/Guy_EscapeState.h"   
#include "../StatesStuff/Guy_StunState.h"
#include "../StatesStuff/Guy_AttackState.h"
#include "../Gathering of Components/DevilAnimComponent.h"
#include "../Gathering of Components/GuyAnimComponent.h"
#include "../Gathering of Components/CollisionComponent.h"

GameEntity *NPCBuilder::BuildZombie(const std::string &zeName, Vector3 &boundary, std::vector<GameEntity*> &enemyList, std::vector<GameEntity*> &allyList, const Vector3 &zePos)
{
    GameEntity *go = new GameEntity;
    static size_t zeEntityNum = 0;
    std::ostringstream ss;
    ss << zeName << ++zeEntityNum;
    go->setName(ss.str());
    enemyList.push_back(go);

    MeshComponent *zeMesh = new MeshComponent();
    GraphicsEntity *zeGraphics = dynamic_cast<GraphicsEntity*>(&Scene_System::accessing().getGraphicsScene());
    zeMesh->onNotify(zeGraphics->getMeshID("ZombieSprite"));
    go->addComponent(MeshComponent::g_CompID_.getValue(), zeMesh);

    PhysicsComponent *zePhysics = new PhysicsComponent();
    zePhysics->setPos(zePos);
    zePhysics->setSize(Vector3(25, 25, 1));
    zePhysics->setBoundary(boundary);
    go->addComponent(PhysicsComponent::g_ID_, zePhysics);

    StateMachineComponent *zeFSM = new StateMachineComponent;
    go->addComponent(StateMachineComponent::ID_.getValue(), zeFSM);
    zeFSM->addStates(*new IdleState, IdleState::ID_);
    zeFSM->addStates(*new ZombieTarget, ZombieTarget::ID_);
    zeFSM->addStates(*new GoThereState, GoThereState::ID_);
    zeFSM->addStates(*new MeleeAttackState, MeleeAttackState::ID_);
    zeFSM->addStates(*new ZombieCharge, ZombieCharge::ID_);
    zeFSM->getSpecificStates(MeleeAttackState::ID_).onNotify(20.f);
    zeFSM->getSpecificStates(MeleeAttackState::ID_).onNotify(-1.f);
    zeFSM->getSpecificStates(IdleState::ID_).onNotify(40.f);
    zeFSM->getSpecificStates(ZombieTarget::ID_).onNotify(40.f);
    zeFSM->getSpecificStates(ZombieTarget::ID_).onNotify(-30.f);
    zeFSM->getSpecificStates(ZombieTarget::ID_).onNotify(2);
    zeFSM->getSpecificStates(ZombieCharge::ID_).onNotify(30.f);
    zeFSM->getSpecificStates(ZombieCharge::ID_).onNotify(2);

    AllyEnemyComponent *toRecogniseEnemyAlly = new AllyEnemyComponent;
    toRecogniseEnemyAlly->setAllyList(enemyList).setEnemyList(allyList);
    go->addComponent(AllyEnemyComponent::ID_, toRecogniseEnemyAlly);

    SpeedComponent *zeSpeed = new SpeedComponent;
    go->addComponent(SpeedComponent::ID_, zeSpeed);
    zeSpeed->onNotify(20);

    HPandDPComponent *zeHPandDP = new HPandDPComponent;
    go->addComponent(HPandDPComponent::ID_, zeHPandDP);
    zeHPandDP->setHealth(100);
    zeHPandDP->setDamage(10);

    go->addComponent(ZombieAnimComp::ID_, new ZombieAnimComp());

    return go;
}
GameEntity *NPCBuilder::BuildDog(const std::string &zeName, Vector3 &boundary, std::vector<GameEntity*> &enemyList, std::vector<GameEntity*> &allyList, const Vector3 &zePos)
{
    GameEntity *go = new GameEntity;
    std::ostringstream ss;
    static size_t zeIDNum = 0;
    ss << zeName << ++zeIDNum;
    go->setName(ss.str());
    allyList.push_back(go);

    MeshComponent *zeMesh = new MeshComponent();
    GraphicsEntity *zeGraphics = dynamic_cast<GraphicsEntity*>(&Scene_System::accessing().getGraphicsScene());
    zeMesh->onNotify(zeGraphics->getMeshID("DogSprite"));
    go->addComponent(MeshComponent::g_CompID_.getValue(), zeMesh);
    //go->addComponent(MyMeshComponent::ID_, &zeMesh);

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
    zeFSM->getSpecificStates(DogBarkState::ID_).onNotify(25.f);
    zeFSM->addStates(*new GoThereState, GoThereState::ID_);
    zeFSM->addStates(*new DogBite, DogBite::ID_);
    zeFSM->getSpecificStates(DogBite::ID_).onNotify(50.f);
    zeFSM->getSpecificStates(DogBite::ID_).onNotify(-0.5f);
    zeFSM->getSpecificStates(DogBite::ID_).onNotify(5);
    zeFSM->getSpecificStates(DogBarkState::ID_).onNotify(5);

    AllyEnemyComponent *toRecogniseEnemyAlly = new AllyEnemyComponent;
    toRecogniseEnemyAlly->setAllyList(allyList).setEnemyList(enemyList);
    go->addComponent(AllyEnemyComponent::ID_, toRecogniseEnemyAlly);

    SpeedComponent *zeSpeed = new SpeedComponent;
    go->addComponent(SpeedComponent::ID_, zeSpeed);
    zeSpeed->onNotify(20.f);

    HPandDPComponent *zeHPandDP = new HPandDPComponent;
    go->addComponent(HPandDPComponent::ID_, zeHPandDP);
    zeHPandDP->setHealth(25);
    zeHPandDP->setDamage(3);

    go->addComponent(DogAnimComp::ID_, new DogAnimComp());
    
    return go;
}

GameEntity *NPCBuilder::BuildDevil(const std::string &zeName, Vector3 &boundary, std::vector<GameEntity*> &enemyList, std::vector<GameEntity*> &allyList, const Vector3 &zePos)
{
	GameEntity *Devil = new GameEntity();
	Devil->setName(zeName);
	MeshComponent *devilMesh = new MeshComponent();
	GraphicsEntity *zeGraphics = dynamic_cast<GraphicsEntity*>(&Scene_System::accessing().getGraphicsScene());
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
	DeviltoRecogniseEnemyAlly->setAllyList(enemyList).setEnemyList(allyList);
	Devil->addComponent(AllyEnemyComponent::ID_, DeviltoRecogniseEnemyAlly);
	Devil->addComponent(DevilAnimComp::ID_, new DevilAnimComp());
	
	enemyList.push_back(Devil);
	return Devil;
}
GameEntity *NPCBuilder::BuildGuy(const std::string &zeName, Vector3 &boundary, std::vector<GameEntity*> &enemyList, std::vector<GameEntity*> &allyList, const Vector3 &zePos)
{
	GameEntity *Guy = new GameEntity();
	Guy->setName(zeName);
	MeshComponent *guyMesh = new MeshComponent();
	GraphicsEntity *zeGraphics = dynamic_cast<GraphicsEntity*>(&Scene_System::accessing().getGraphicsScene());
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
	GuytoRecogniseEnemyAlly->setAllyList(allyList).setEnemyList(enemyList);
	Guy->addComponent(AllyEnemyComponent::ID_, GuytoRecogniseEnemyAlly);
	Guy->addComponent(GuyAnimComp::ID_, new GuyAnimComp());

	allyList.push_back(Guy);
	return Guy;
}

GameEntity *NPCBuilder::BuildBullet(const std::string &zeName, Vector3 &boundary, std::vector<GameEntity*> &enemyList, std::vector<GameEntity*> &allyList, std::vector<GameEntity*> &listtodespawn, const Vector3 &zePos)
{
	GameEntity* bullet = new GameEntity();
	bullet->setName(zeName);
	MeshComponent *bulletMesh = new MeshComponent();
	GraphicsEntity *zeGraphics = dynamic_cast<GraphicsEntity*>(&Scene_System::accessing().getGraphicsScene());
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
	bullet->addComponent(HPandDPComponent::ID_, new HPandDPComponent(100, 49));
	CollisionComponent *bulletCollision = new CollisionComponent;
	bulletCollision->setDespawnList(listtodespawn).setEnemyList(enemyList);
	bullet->addComponent(CollisionComponent::ID_, bulletCollision);

	return bullet;
}