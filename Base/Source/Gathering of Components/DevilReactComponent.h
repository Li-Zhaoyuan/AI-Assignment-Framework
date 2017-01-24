#pragma once

#include "../GenericECS/GenericComponent.h"
class StateMachineComponent;

class DevilReactComponent : public GenericComponent
{
public:
	DevilReactComponent();
	virtual ~DevilReactComponent();

	virtual bool onNotify(const std::string &zeEvent);
	virtual bool onNotify(const int &zeEvent);

	static const unsigned char ID_ = 9;
protected:
	std::string receivedMessage;
	StateMachineComponent *FSM_;
	int chanceToReact;
	bool HasReactToMessage;
};