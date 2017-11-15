#pragma once
#include <string>

class FVector3
{
public:
	FVector3();
	FVector3(float _x_y_z);
	FVector3(float _x, float _y, float _z);
	~FVector3();

	float x;
	float y;
	float z;

	FVector3 operator+(const FVector3& newVector3);
	FVector3 operator-(const FVector3& newVector3);
	FVector3 operator*(const FVector3& newVector3);
	FVector3 operator*(const float multiplier);
	FVector3 operator/(const FVector3& newVector3);

	float GetMagnitude();
	void Normalize();

	static FVector3 Lerp(FVector3 start, FVector3 end, float percent);

	std::string ToString();

private:
	float _magnitude;
};

