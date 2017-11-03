#pragma once

#include <string>

class FVector2
{
public:
	FVector2();
	FVector2(float _x_y);
	FVector2(float _x, float _y);
	~FVector2();

	float x;
	float y;

	FVector2 operator+(const FVector2& newVector2);
	FVector2 operator-(const FVector2& newVector2);
	FVector2 operator*(const FVector2& newVector2);
	FVector2 operator*(const float multiplier);
	FVector2 operator/(const FVector2& newVector2);

	std::string ToString();
};

