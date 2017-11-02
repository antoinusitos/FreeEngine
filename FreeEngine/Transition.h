#pragma once

#include "Data.h"

class State;

class Transition
{
public:
	Transition();
	~Transition();

	State* newState;
	Condition condition;
};
