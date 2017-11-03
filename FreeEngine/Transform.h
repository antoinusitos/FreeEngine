#pragma once

#include "FVector3.h"

class Transform
{
public:
	Transform();
	~Transform();

	FVector3 position;
	FVector3 rotation;
	FVector3 scale;
};

