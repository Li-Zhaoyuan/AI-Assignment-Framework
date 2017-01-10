#pragma once

#include "../GenericECS/GenericSystem.h"
#include "../Classes/singletontemplate.h"
#include <map>

class MessageSystem : public GenericSystem, public SingletonTemplate<MessageSystem>
{
public:

    std::map<size_t, std::string> ImportanceMessageDV;
    std::map < size_t, std::string> ImportanceMessageHM;
};