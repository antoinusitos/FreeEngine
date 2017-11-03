#include "FVector2.h"

#include <iostream>

FVector2::FVector2()
{
	x = 0;
	y = 0;
}

FVector2::FVector2(float _x_y)
{
	x = _x_y;
	y = _x_y;
}

FVector2::FVector2(float _x, float _y)
{
	x = _x;
	y = _y;
}

FVector2::~FVector2()
{
}

FVector2 FVector2::operator+(const FVector2& newVector2)
{
	return FVector2(x + newVector2.x, y + newVector2.y);
}

FVector2 FVector2::operator-(const FVector2& newVector2)
{
	return FVector2(x - newVector2.x, y - newVector2.y);
}

FVector2 FVector2::operator*(const FVector2& newVector2)
{
	return FVector2(x * newVector2.x, y * newVector2.y);
}

FVector2 FVector2::operator*(const float multiplier)
{
	return FVector2(x * multiplier, y * multiplier);
}

FVector2 FVector2::operator/(const FVector2& newVector2)
{
	return FVector2(x / newVector2.x, y / newVector2.y);
}

std::string FVector2::ToString()
{
	return std::string("x:" + std::to_string(x) + ", y:" + std::to_string(y));
}