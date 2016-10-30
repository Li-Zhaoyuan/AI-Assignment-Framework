#ifndef FORWARD_COMMAND_H
#define FORWARD_COMMAND_H

#include "CommandComponent.h"

class ForwardCommand : public CommandComponent
{
public:
    virtual ~ForwardCommand();
    static unsigned char theKey;

    virtual unsigned short getKey();

private:
    ForwardCommand();
    static ForwardCommand *zeCommand;
};

#endif