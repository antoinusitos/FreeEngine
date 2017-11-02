#pragma once

#include "Data.h"
#include <vector>

class State;

class Transition
{
public:
	Transition();
	~Transition();

	void AddCondition(Condition* condition);

	State* newState;
	std::vector<Condition*> conditions;
};
