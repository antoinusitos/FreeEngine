#include "Transition.h"
#include "State.h"

Transition::Transition()
{
}

Transition::~Transition()
{
}

void Transition::AddCondition(Condition* condition)
{
	conditions.push_back(condition);
}