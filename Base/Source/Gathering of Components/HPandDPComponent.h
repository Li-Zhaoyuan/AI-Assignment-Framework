#pragma once

#include "../GenericECS/GenericComponent.h"

class HPandDPComponent : public GenericComponent
{
public:
    HPandDPComponent();
    HPandDPComponent(const int &zeHealth, const int &zeDamage);
    virtual ~HPandDPComponent();

    virtual void Init();
    
    void setHealth(const int &zeHealth);
    void setDamage(const int &zeDMG);

    virtual bool onNotify(const int &zeEvent);

    static const unsigned char ID_ = 4;

    int &getHealth();
    int &getDamage();

private:
    int health_, damage_;
};