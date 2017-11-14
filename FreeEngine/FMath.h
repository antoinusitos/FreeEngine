#pragma once

#include <memory>
#include <mutex>

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
			//std::cout << "Getting  Window instance" << '\n';
		});

		return *(_instance.get());
	}

	static float Lerp(const float start, const float end, float percent);

	const static float Clamp(const float value, const float min, const float max);

	// Random float between min [inclusive] and max [exclusive]
	const static float Random(const float min, const float max);
	// Random int between min [inclusive] and max [exclusive]
	const static int Random(const int min, const int max);

//Variables
private:
	// Unique instance of the time
	static std::unique_ptr<FMath> _instance;
	static std::once_flag onceFlag;
};

