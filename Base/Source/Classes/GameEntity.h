#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "../GenericECS/GenericEntity.h"
#include "../GenericECS/GenericComponent.h"
#include <set>

#ifndef MAX_NUM_COMPONENTS
#define MAX_NUM_COMPONENTS 32U
#endif

class GameEntity : public GenericEntity
{
public: //Do go and investigate union
    GameEntity();
    virtual ~GameEntity();

    virtual void Init();
    virtual void Update(double dt);
    virtual void Exit();
    
    bool addComponent(const size_t &zeCompID, GenericComponent *zeComponent);
    GenericComponent &getComponent(const size_t &zeNum);
    
    bool turnOffComponent(const size_t &zeNum);
    bool turnOnComponent(const size_t &zeNum);
    bool removeComponent(const size_t &zeNum);

protected:
    bool ComponentActive[MAX_NUM_COMPONENTS];   //Referring to Data Locality Pattern here.
    GenericComponent *ComponentsItHeld[MAX_NUM_COMPONENTS];
    std::set<size_t> whatComponentAreThr;
};

#endif