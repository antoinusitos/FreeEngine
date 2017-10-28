#include "Vector3.h"
#include <iostream>

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3::~Vector3()
{
}

Vector3 Vector3::operator+(const Vector3& newVector3)
{
	return Vector3(x + newVector3.x, y + newVector3.y, z + newVector3.z);
}

Vector3 Vector3::operator-(const Vector3& newVector3)
{
	return Vector3(x - newVector3.x, y - newVector3.y, z - newVector3.z);
}

Vector3 Vector3::operator*(const Vector3& newVector3)
{
	return Vector3(x * newVector3.x, y * newVector3.y, z * newVector3.z);
}

Vector3 Vector3::operator*(const float multiplier)
{
	return Vector3(x * multiplier, y * multiplier, z * multiplier);
}

Vector3 Vector3::operator/(const Vector3& newVector3)
{
	return Vector3(x / newVector3.x, y / newVector3.y, z / newVector3.z);
}

std::string Vector3::ToString()
{
	return std::string("x:" + std::to_string(x) + ", y:" + std::to_string(y) + ", z:" + std::to_string(z));
}