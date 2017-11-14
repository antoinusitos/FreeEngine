#include "FMath.h"
#include <stdlib.h>
#include <time.h>

std::unique_ptr<FMath> FMath::_instance;
std::once_flag FMath::onceFlag;

FMath::FMath()
{
	srand(time(NULL));
}

FMath::~FMath()
{
}

float FMath::Lerp(const float start, const float end, float percent)
{
	if (percent < 0) percent = 0;
	else if (percent > 1) percent = 1;
	float toReturn = (start + Clamp(percent, 0.f, 1.f)*(end - start));
	return toReturn;
}

const float FMath::Clamp(const float value, const float min, const float max)
{
	if (value < min) return min;
	else if (value > max) return max;
	return value;
}

// Random float between min [inclusive] and max [exclusive]
const float FMath::Random(const float min, const float max)
{
	return (rand() / (double)RAND_MAX) * (max - min) + min;
}

// Random int between min [inclusive] and max [exclusive]
const int FMath::Random(const int min, const int max)
{
	return rand() % (max - min) + min;
}