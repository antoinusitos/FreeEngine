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

void FVector3::operator=(const FVector3& newVector3)
{
	x = newVector3.x;
	y = newVector3.y;
	z = newVector3.z;
}

void FVector3::operator+=(const FVector3& newVector3)
{
	x += newVector3.x;
	y += newVector3.y;
	z += newVector3.z;
}

void FVector3::operator-=(const FVector3& newVector3)
{
	x -= newVector3.x;
	y -= newVector3.y;
	z -= newVector3.z;
}

void FVector3::operator*=(const FVector3& newVector3)
{
	x *= newVector3.x;
	y *= newVector3.y;
	z *= newVector3.z;
}

void FVector3::operator/=(const FVector3& newVector3)
{
	x /= newVector3.x;
	y /= newVector3.y;
	z /= newVector3.z;
}

FVector3 FVector3::Lerp(FVector3 start, FVector3 end, float percent)
{
	return (start + (end - start) * percent);
}

std::string FVector3::ToString()
{
	return std::string("x:" + std::to_string(x) + ", y:" + std::to_string(y) + ", z:" + std::to_string(z));
}

float FVector3::GetMagnitude()
{
	_magnitude = sqrt(x*x + y*y + z*z);
	return _magnitude;
}

void FVector3::Normalize()
{
	float m = GetMagnitude();
	x = x / m;
	y = y / m;
	z = z / m;
}

float FVector3::Distance(const FVector3& start, const FVector3& end)
{
	return sqrt(
		(end.x - start.x) * (end.x - start.x) +
		(end.y - start.y) * (end.y - start.y) +
		(end.z - start.z) * (end.z - start.z) 
	);
}

float FVector3::DotProduct(const FVector3& start, const FVector3& end)
{
	return start.x * end.x + start.y * end.y + start.z * end.z;
}

FVector3 FVector3::CrossProduct(const FVector3& start, const FVector3& end)
{
	FVector3 toReturn = FVector3();

	toReturn.x = start.y * end.z - start.z * end.y;
	toReturn.y = start.z * end.x - start.x * end.z;
	toReturn.z = start.x * end.y - start.y * end.x;

	return toReturn;
}