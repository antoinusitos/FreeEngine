#pragma once
#include <string>

class FVector4
{
public:
	FVector4();
	FVector4(float _x_y_z_w);
	FVector4(float _x, float _y, float _z, float _w);
	~FVector4();

	float x;
	float y;
	float z;
	float w;

	FVector4 operator+(const FVector4& newVector4);
	FVector4 operator-(const FVector4& newVector4);
	FVector4 operator*(const FVector4& newVector4);
	FVector4 operator*(const float multiplier);
	FVector4 operator/(const FVector4& newVector4);
	void operator=(const FVector4& newVector4);
	void operator+=(const FVector4& newVector4);
	void operator-=(const FVector4& newVector4);
	void operator*=(const FVector4& newVector4);
	void operator/=(const FVector4& newVector4);

	float GetMagnitude();
	void Normalize();

	static FVector4 Lerp(FVector4 start, FVector4 end, float percent);

	std::string ToString();

private:
	float _magnitude;
};

