#pragma once
#include <string>

class Vector3
{
public:
	Vector3();
	Vector3(float _x, float _y, float _z);
	~Vector3();

	float x;
	float y;
	float z;

	Vector3 operator+(const Vector3& newVector3);
	Vector3 operator-(const Vector3& newVector3);
	Vector3 operator*(const Vector3& newVector3);
	Vector3 operator*(const float multiplier);
	Vector3 operator/(const Vector3& newVector3);

	std::string ToString();
};

