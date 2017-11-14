#include "Transform.h"
#include <iostream>

Transform::Transform()
{
	position = FVector3(0);
	rotation = FVector3(0);
	scale = FVector3(1);
}

Transform::~Transform()
{
}

std::string Transform::ToString()
{
	return std::string(
		"{" + std::to_string(position.x) + ";" + std::to_string(position.y) + ";" + std::to_string(position.z) + ";" + "}"+
		"{" + std::to_string(rotation.x) + ";" + std::to_string(rotation.y) + ";" + std::to_string(rotation.z) + ";" + "}" +
		"{" + std::to_string(scale.x) + ";" + std::to_string(scale.y) + ";" + std::to_string(scale.z) + ";" + "}"
	);
}

Transform Transform::ReadString(const std::string s)
{
	std::string toParse = s;
	Transform t = Transform();

	std::string delimiter = "{";
	std::string delimiterSecond = ";";
	std::string delimiterThird = "}";

	// POSITION

	toParse.erase(0, delimiter.length());


	for (int i = 0; i < 3; i++)
	{
		std::string token = toParse.substr(0, toParse.find(delimiterSecond));
		size_t posTemp = toParse.find(delimiterSecond);
		if (i == 0)
			t.position.x = std::atof(token.c_str());
		else if (i == 1)
			t.position.y = std::atof(token.c_str());
		else if (i == 2)
			t.position.z = std::atof(token.c_str());
		toParse.erase(0, posTemp + delimiterSecond.length());
	}
	toParse.erase(0, delimiterThird.length());

	// ROTATION

	toParse.erase(0, delimiter.length());

	for (int i = 0; i < 3; i++)
	{
		std::string token = toParse.substr(0, toParse.find(delimiterSecond));
		size_t posTemp = toParse.find(delimiterSecond);
		if (i == 0)
			t.rotation.x = std::atof(token.c_str());
		else if (i == 1)
			t.rotation.y = std::atof(token.c_str());
		else if (i == 2)
			t.rotation.z = std::atof(token.c_str());
		toParse.erase(0, posTemp + delimiterSecond.length());
	}

	toParse.erase(0, delimiterThird.length());

	// SCALE

	toParse.erase(0, delimiter.length());

	for (int i = 0; i < 3; i++)
	{
		std::string token = toParse.substr(0, toParse.find(delimiterSecond));
		size_t posTemp = toParse.find(delimiterSecond);
		if (i == 0)
			t.scale.x = std::atof(token.c_str());
		else if (i == 1)
			t.scale.y = std::atof(token.c_str());
		else if (i == 2)
			t.scale.z = std::atof(token.c_str());
		toParse.erase(0, posTemp + delimiterSecond.length());
	}

	toParse.erase(0, delimiterThird.length());

	return t;
}