#include "FMath.h"
#include <stdlib.h>
#include <time.h>
#include "ResourcesManager.h"

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

const float FMath::Clamp01(const float value)
{
	if (value < 0) return 0;
	else if (value > 1) return 1;
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

const float FMath::Map(const float value, const float fromMin, const float fromMax, const float toMin, const float toMax)
{
	return toMin + ((toMax - toMin) / (fromMax - fromMin)) * (value - fromMin);
}

const FVector4 FMath::GetRandomPixelColor(const std::string fileName)
{
	sf::Image image = ResourcesManager::Instance().GetImage(fileName);
	unsigned int width = image.getSize().x;
	unsigned int height = image.getSize().y;

	sf::Color col = image.getPixel(Random(0, width - 1), Random(0, height - 1));
	return FVector4(col.r, col.g, col.b, col.a);
}

const std::vector<FVector4> FMath::GetPixels(const std::string fileName)
{
	sf::Image image = ResourcesManager::Instance().GetImage(fileName);
	unsigned int width = image.getSize().x;
	unsigned int height = image.getSize().y;
	
	std::vector<FVector4> toReturn;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			sf::Color col = image.getPixel(j, i);
			toReturn.push_back(FVector4(col.r, col.g, col.b, col.a));
		}
	}
	return toReturn;
}