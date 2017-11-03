#include "FVector3.h"
#include <iostream>

FVector3::FVector3()
{
	x = 0;
	y = 0;
	z = 0;
}

FVector3::FVector3(float _x_y_z)
{
	x = _x_y_z;
	y = _x_y_z;
	z = _x_y_z;
}

FVector3::FVector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

FVector3::~FVector3()
{
}

FVector3 FVector3::operator+(const FVector3& newVector3)
{
	return FVector3(x + newVector3.x, y + newVector3.y, z + newVector3.z);
}

FVector3 FVector3::operator-(const FVector3& newVector3)
{
	return FVector3(x - newVector3.x, y - newVector3.y, z - newVector3.z);
}

FVector3 FVector3::operator*(const FVector3& newVector3)
{
	return FVector3(x * newVector3.x, y * newVector3.y, z * newVector3.z);
}

FVector3 FVector3::operator*(const float multiplier)
{
	return FVector3(x * multiplier, y * multiplier, z * multiplier);
}

FVector3 FVector3::operator/(const FVector3& newVector3)
{
	return FVector3(x / newVector3.x, y / newVector3.y, z / newVector3.z);
}

std::string FVector3::ToString()
{
	return std::string("x:" + std::to_string(x) + ", y:" + std::to_string(y) + ", z:" + std::to_string(z));
}