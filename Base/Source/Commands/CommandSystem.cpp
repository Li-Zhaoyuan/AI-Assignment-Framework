#include "CommandSystem.h"
#include "../Systems/Scene_System.h"
#include "timer.h"

void CommandSystem::Init()
{

}

void CommandSystem::Update(double dt)
{
    for (std::vector<CommandComponent*>::iterator it = allTheCommands_.begin(), end = allTheCommands_.end(); it != end; ++it)
    {
        unsigned short numKey = (*it)->getKey();
        if (isKeyPressed(numKey))
        {
            Scene_System::accessing().getCurrScene().onNotify(numKey);
        }
    }
}

void CommandSystem::Exit()
{
    for (auto it : allTheCommands_)
    {
        delete it;
        it = nullptr;
    }
    allTheCommands_.clear();
}

void CommandSystem::addCommands(CommandComponent &zeCommand)
{
    allTheCommands_.push_back(&zeCommand);
}

bool CommandSystem::isKeyPressed(unsigned short &key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}