#pragma once

#include "FVector3.h"
#include <string>

class Transform
{
public:
	Transform();
	~Transform();

	FVector3 position;
	FVector3 rotation;
	FVector3 scale;

	std::string ToString();

	static Transform ReadString(const std::string s);
};

