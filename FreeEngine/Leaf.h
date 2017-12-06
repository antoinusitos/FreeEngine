#pragma once
#include "Component.h"

class Composite;

class Leaf : public Component
{
public:
	Leaf();
	~Leaf();

	bool init = false;
};

