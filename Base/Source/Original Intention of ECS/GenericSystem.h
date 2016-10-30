/******************************************************************************/
/*!
\file   GenericSystem.h
\author Lee Sek Heng
\par email: 150629Z@mymail.nyp.edu.sg
\brief
A Generic System that defines all the system and make them compatible with each other
*/
/******************************************************************************/
#ifndef GENERIC_SYSTEM_H
#define GENERIC_SYSTEM_H

#include "../Classes/singletontemplate.h"
#include <string>

class GenericSystem
{
public:
    virtual void Init() = 0;
    virtual void Update(double dt) = 0;
    virtual void Exit() = 0;

    virtual bool onNotify(const std::string &zeEvent) { return false; }
    virtual bool onNotify(const int &zeEvent) { return false; }
    virtual bool onNotify(const float &zeEvent) { return false; }
    virtual bool onNotify(const double &zeEvent) { return false; }
    virtual bool onNotify(const GenericSystem &zeEvent) { return false; }

    void setName(const std::string &zeName) { name_ = zeName; }
    std::string getName() { return name_; }

protected:
    std::string name_;
};

#endif