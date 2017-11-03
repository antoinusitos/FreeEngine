#include "Transition.h"
#include "State.h"

Transition::Transition()
{
}

Transition::~Transition()
{
	for (std::vector<Condition*>::iterator it = conditions.begin(); it != conditions.end(); ++it)
	{
		delete (*it);
	}
	conditions.clear();
}

void Transition::AddCondition(Condition* condition)
{
	conditions.push_back(condition);
}