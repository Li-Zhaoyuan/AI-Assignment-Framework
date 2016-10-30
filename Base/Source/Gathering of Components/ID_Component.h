#ifndef ID_COMPONENT_H
#define ID_COMPONENT_H

#include "../GenericECS/GenericComponent.h"

class ID_Component : public GenericComponent
{
public:
    ID_Component() {}
    ID_Component(const unsigned short &zeID) { zeID_ = zeID; }
    virtual ~ID_Component() {}

    virtual bool onNotify(const int &zeEvent) {
        if (zeEvent >= 0)
        {
            zeID_ = zeEvent;
            return true;
        }
        return false;
    };
    unsigned short &getValue() { return zeID_; }

protected:
    unsigned short zeID_;
};

#endif