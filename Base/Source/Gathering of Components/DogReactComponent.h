#pragma once

#include "../GenericECS/GenericComponent.h"

class DogReactComponent : public GenericComponent
{
public:
    DogReactComponent();
    virtual ~DogReactComponent();

    virtual bool onNotify(const std::string &zeEvent);

    static const unsigned char ID_ = 9;
protected:
    std::string receivedMessage;
};