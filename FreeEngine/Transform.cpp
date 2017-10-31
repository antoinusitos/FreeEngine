#include "Transform.h"

Transform::Transform()
{
	position = Vector3();
	rotation = Vector3();
	scale = Vector3(1, 1, 1);
}

Transform::~Transform()
{
}
