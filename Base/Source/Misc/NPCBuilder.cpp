#include "NPCBuilder.h"
#include "../Gathering of Components/HPandDPComponent.h"
#include "../Gathering of Components/PhysicsComponent.h"
#include "../Gathering of Components/SpeedComponent.h"
#include "../Gathering of Components/MeshComponent.h"
#include "../Systems/Scene_System.h"
#include "../Scenes/GraphicsEntity.h"

GameEntity *NPCBuilder::BuildZombie(const std::string &zeName, const Vector3 &boundary, std::vector<GameEntity*> &enemyList, std::vector<GameEntity*> &allyList, const Vector3 &zePos)
{
    GameEntity *go = new GameEntity;
    go->setName(zeName);
    enemyList.push_back(go);
    MeshComponent *zeMesh = new MeshComponent();
    GraphicsEntity *zeGraphics = dynamic_cast<GraphicsEntity*>(&Scene_System::accessing().getGraphicsScene());
    zeMesh->onNotify(zeGraphics->getMeshID("greenCube"));
    go->addComponent(MeshComponent::g_CompID_.getValue(), zeMesh);
    PhysicsComponent *zePhysics = new PhysicsComponent();
    zePhysics->setPos(zePos);
    zePhysics->setSize(Vector3(50, 50, 1));
    go->addComponent(PhysicsComponent::g_ID_, zePhysics);

    return go;
}
GameEntity *NPCBuilder::BuildDog(const std::string &zeName, const Vector3 &boundary, std::vector<GameEntity*> &enemyList, std::vector<GameEntity*> &allyList, const Vector3 &zePos)
{
    GameEntity *go = new GameEntity;
    return go;
}
