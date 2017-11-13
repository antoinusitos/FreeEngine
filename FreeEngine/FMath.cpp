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

float FMath::Lerp(float start, float end, float percent)
{
	if (percent < 0) percent = 0;
	else if (percent > 1) percent = 1;
	float toReturn = (start + Clamp(percent, 0.f, 1.f)*(end - start));
	return toReturn;
}

float FMath::Clamp(float value, float min, float max)
{
	if (value < min) return min;
	else if (value > max) return max;
	return value;
}

// Random float between min [inclusive] and max [exclusive]
float FMath::Random(float min, float max)
{
	return (rand() / (double)RAND_MAX) * (max - min) + min;
}

// Random int between min [inclusive] and max [exclusive]
int FMath::Random(int min, int max)
{
	return rand() % (max - min) + min;
}