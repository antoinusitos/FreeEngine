#include "FVector4.h"
#include <iostream>

FVector4::FVector4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

FVector4::FVector4(float _x_y_z_w)
{
	x = _x_y_z_w;
	y = _x_y_z_w;
	z = _x_y_z_w;
	w = _x_y_z_w;
}

FVector4::FVector4(float _x, float _y, float _z, float _w)
{
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

FVector4::~FVector4()
{
}

FVector4 FVector4::operator+(const FVector4& newVector4)
{
	return FVector4(x + newVector4.x, y + newVector4.y, z + newVector4.z, w + newVector4.w);
}

FVector4 FVector4::operator-(const FVector4& newVector4)
{
	return FVector4(x - newVector4.x, y - newVector4.y, z - newVector4.z, w - newVector4.w);
}

FVector4 FVector4::operator*(const FVector4& newVector4)
{
	return FVector4(x * newVector4.x, y * newVector4.y, z * newVector4.z, w * newVector4.w);
}

FVector4 FVector4::operator*(const float multiplier)
{
	return FVector4(x * multiplier, y * multiplier, z * multiplier, w * multiplier);
}

FVector4 FVector4::operator/(const FVector4& newVector4)
{
	return FVector4(x / newVector4.x, y / newVector4.y, z / newVector4.z, w / newVector4.w);
}

void FVector4::operator=(const FVector4& newVector4)
{
	x = newVector4.x;
	y = newVector4.y;
	z = newVector4.z;
	w = newVector4.w;
}

void FVector4::operator+=(const FVector4& newVector4)
{
	x += newVector4.x;
	y += newVector4.y;
	z += newVector4.z;
	w += newVector4.w;
}

void FVector4::operator-=(const FVector4& newVector4)
{
	x -= newVector4.x;
	y -= newVector4.y;
	z -= newVector4.z;
	w -= newVector4.w;
}

void FVector4::operator*=(const FVector4& newVector4)
{
	x *= newVector4.x;
	y *= newVector4.y;
	z *= newVector4.z;
	w *= newVector4.w;
}

void FVector4::operator/=(const FVector4& newVector4)
{
	x /= newVector4.x;
	y /= newVector4.y;
	z /= newVector4.z;
	w /= newVector4.w;
}

FVector4 FVector4::Lerp(FVector4 start, FVector4 end, float percent)
{
	return (start + (end - start) * percent);
}

std::string FVector4::ToString()
{
	return std::string("x:" + std::to_string(x) + ", y:" + std::to_string(y) + ", z:" + std::to_string(z) + ", w:" + std::to_string(w));
}

float FVector4::GetMagnitude()
{
	_magnitude = sqrt(x*x + y*y + z*z + w*w);
	return _magnitude;
}

void FVector4::Normalize()
{
	float m = GetMagnitude();
	x = x / m;
	y = y / m;
	z = z / m;
	w = w / m;
}