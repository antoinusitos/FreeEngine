#include "FMath.h"

FMath::FMath()
{
}

FMath::~FMath()
{
}

float FMath::Lerp(float start, float end, float percent)
{
	if (percent < 0) percent = 0;
	else if (percent > 1) percent = 1;
	float toReturn = (start + percent*(end - start));
	return toReturn;
}