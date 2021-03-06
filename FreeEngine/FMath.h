#pragma once

#include <memory>
#include <mutex>
#include "FVector4.h"
#include <vector>

class FMath
{
public:
	FMath();
	~FMath();

	// Get a unique instance of the time
	static FMath& FMath::Instance()
	{
		std::call_once(FMath::onceFlag, []() {
			_instance.reset(new FMath);
		});

		return *(_instance.get());
	}

	static float Lerp(const float start, const float end, float percent);

	const static float Clamp(const float value, const float min, const float max);
	const static float Clamp01(const float value);

	// Random float between min [inclusive] and max [exclusive]
	const static float Random(const float min, const float max);
	// Random int between min [inclusive] and max [exclusive]
	const static int Random(const int min, const int max);

	// Map a value from a range to another range
	const static float Map(const float value, const float fromMin, const float fromMax, const float toMin, const float toMax);

	const static FVector4 GetRandomPixelColor(const std::string fileName);
	const static std::vector<FVector4> GetPixels(const std::string fileName);

//Variables
private:
	// Unique instance of the time
	static std::unique_ptr<FMath> _instance;
	static std::once_flag onceFlag;
};

