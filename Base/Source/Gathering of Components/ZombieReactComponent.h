#pragma once

#include "../GenericECS/GenericComponent.h"
class StateMachineComponent;

class ZombieReactComponent : public GenericComponent
{
public:
	ZombieReactComponent();
	virtual ~ZombieReactComponent();

	virtual bool onNotify(const std::string &zeEvent);

	static const unsigned char ID_ = 9;
protected:
	std::string receivedMessage;
	StateMachineComponent *FSM_;
};