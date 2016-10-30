/******************************************************************************/
/*!
\file           GenericEntity.h
\author      Lee Sek Heng
\par            email: 150629Z@mymail.nyp.edu.sg
\brief
A Generic Entity so that polymorphism will make life easier when all objects inheirits from it.
*/
/******************************************************************************/
#ifndef GENERIC_ENTITY_H
#define GENERIC_ENTITY_H

//#include "GenericComponent.h"
#include <string>
//#include <set>

//class GenericComponent;
//
//#ifndef MAX_NUM_COMPONENTS
//#define MAX_NUM_COMPONENTS 32U
//#endif

/******************************************************************************/
/*!
Class GenericEntity:
\brief  Defines a GenericEntity and it's methods.
*/
/******************************************************************************/
class GenericEntity
{
public:
    GenericEntity();
    virtual ~GenericEntity();

    //virtual void Init();
    //virtual void Update(double dt);
    //virtual void Exit();

    virtual bool onNotify(const std::string &zeEvent) { return false; };
    virtual bool onNotify(const int &zeEvent) { return false; };
    virtual bool onNotify(const float &zeEvent) { return false; };
    virtual bool onNotify(const double &zeEvent) { return false; };
    virtual bool onNotify(const GenericEntity &zeEvent) { return false; };

    std::string getName() { return name_; };
    void setName(const std::string &zeName) { name_ = zeName; };

    //bool addComponent(const size_t &zeCompID, GenericComponent *zeComponent);
    //GenericComponent &getComponent(const size_t &zeNum);

    //bool turnOffComponent(const size_t &zeNum);
    //bool turnOnComponent(const size_t &zeNum);
    //bool removeComponent(const size_t &zeNum);

protected:
    std::string name_;
    //bool ComponentActive[MAX_NUM_COMPONENTS];   //Referring to Data Locality Pattern here.
    //GenericComponent *ComponentsItHeld[MAX_NUM_COMPONENTS];
    //std::set<size_t> whatComponentAreThr;
};

#endif