#pragma once

#include "Component.h"
#include "Leaf.h"

#include <vector>

class Composite : public Component
{
public:
	Composite();
	~Composite();

	std::vector<Leaf*> components;

	void AddLeaf(Leaf* newLeaf);
	void RemoveLeaf(Leaf* leafToRemove);
};

