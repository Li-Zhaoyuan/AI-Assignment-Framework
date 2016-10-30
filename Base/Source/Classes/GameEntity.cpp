#include "GameEntity.h"

GameEntity::GameEntity()
{
    Init();
}

GameEntity::~GameEntity()
{
    Exit();
}

bool GameEntity::addComponent(const size_t &zeCompID, GenericComponent *zeComponent)
{
#ifdef _DEBUG
    assert(!ComponentsItHeld[zeCompID] && zeCompID < MAX_NUM_COMPONENTS);
#endif
    if (!ComponentsItHeld[zeCompID] && zeCompID < MAX_NUM_COMPONENTS)
    {
        ComponentsItHeld[zeCompID] = zeComponent;
        zeComponent->setEntityOwner(this);
        zeComponent->Init();
        ComponentActive[zeCompID] = true;
        whatComponentAreThr.insert(zeCompID);
        return true;
    }
    return false;
}

GenericComponent &GameEntity::getComponent(const size_t &zeNum)
{
#ifdef _DEBUG
    assert(zeNum < MAX_NUM_COMPONENTS);
#endif
    return *ComponentsItHeld[zeNum];
}

void GameEntity::Init()
{
    name_ = "";
    for (size_t num = 0; num < MAX_NUM_COMPONENTS; ++num)
    {
        ComponentsItHeld[num] = nullptr;
        ComponentActive[num] = false;
    }
}

void GameEntity::Update(double dt)
{
    //Data Locality Pattern here.
    for (std::set<size_t>::iterator it = whatComponentAreThr.begin(), end = whatComponentAreThr.end(); it != end; ++it)
    {
        if (ComponentActive[*it])
            ComponentsItHeld[*it]->Update(dt);
    }
}

void GameEntity::Exit()
{
    for (size_t num = 0; num < MAX_NUM_COMPONENTS; ++num)
    {
        if (ComponentsItHeld[num])
        {
            delete ComponentsItHeld[num];
            ComponentsItHeld[num] = nullptr;
            ComponentActive[num] = false;
        }
    }
    whatComponentAreThr.clear();
}

bool GameEntity::turnOffComponent(const size_t &zeNum)
{
    if (ComponentActive[zeNum] && ComponentsItHeld[zeNum])
    {
        ComponentActive[zeNum] = false;
        return true;
    }
    return true;
}

bool GameEntity::removeComponent(const size_t &zeNum)
{
#ifdef _DEBUG
    assert(zeNum < MAX_NUM_COMPONENTS);
#endif
    if (zeNum < MAX_NUM_COMPONENTS && ComponentsItHeld[zeNum])
    {
        delete ComponentsItHeld[zeNum];
        ComponentsItHeld[zeNum] = nullptr;
        ComponentActive[zeNum] = false;
        whatComponentAreThr.erase(zeNum);
        return true;
    }
    return false;
}

bool GameEntity::turnOnComponent(const size_t &zeNum)
{
#ifdef _DEBUG
    assert(zeNum < MAX_NUM_COMPONENTS);
#endif
    if (zeNum < MAX_NUM_COMPONENTS && ComponentActive[zeNum] == false && ComponentsItHeld[zeNum])
    {
        ComponentActive[zeNum] = true;
        return true;
    }
    return false;
}