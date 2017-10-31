#include "Composite.h"

Composite::Composite()
{
}

Composite::~Composite()
{
}

void Composite::AddLeaf(Leaf* newLeaf)
{
	newLeaf->_parent = this;
	components.push_back(newLeaf);
}

void Composite::RemoveLeaf(Leaf* leafToRemove)
{
	int index = -1;
	bool found = false;
	for (std::vector<Leaf*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		index++;
		if ((*it) == leafToRemove)
		{
			found = true;
			break;
		}
	}

	if (found)
		components.erase(components.begin() + index);
}