#ifndef COMMAND_SYSTEM_H
#define COMMAND_SYSTEM_H

#include "../GenericECS/GenericSystem.h"
#include "../Classes/singletontemplate.h"
#include <vector>
#include "../Gathering of Components/CommandComponent.h"

class CommandSystem : public GenericSystem, public SingletonTemplate<CommandSystem>
{
public:
    virtual void Init();
    virtual void Update(double dt);
    virtual void Exit();

    void addCommands(CommandComponent &zeCommand);

private:
    std::vector<CommandComponent*> allTheCommands_;
    bool isKeyPressed(unsigned short &key);
};

#endif