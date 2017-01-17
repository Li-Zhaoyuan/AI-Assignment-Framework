/******************************************************************************/
/*!
\file           singletontemplate.h
\author      Lee Sek Heng
\par            email: 150629Z@mymail.nyp.edu.sg
\brief
A template for all classes that needs to be a singleton
*/
/******************************************************************************/
#ifndef SINGLETON_TEMPLATE_H
#define SINGLETON_TEMPLATE_H

#include "..\\Misc\\DetectMemoryLeak.h"

template<class Type>
class SingletonTemplate/*<Type>*/
{
public:
    static Type &accessing() {
        //static Type Cant_touch_this;
        //if (Cant_touch_this)
        //return *Cant_touch_this;
        if (!Cant_touch_this)
            Cant_touch_this = new Type();
        return *Cant_touch_this;
    }
    static void Destroy()
    {
        if (Cant_touch_this)
        {
            delete Cant_touch_this;
            Cant_touch_this = nullptr;
        }
    }

protected:
    SingletonTemplate() {};
    virtual ~SingletonTemplate() {};
private:
    static Type *Cant_touch_this;
};

template<class Type>
Type *SingletonTemplate<Type>::Cant_touch_this = nullptr;

#endif