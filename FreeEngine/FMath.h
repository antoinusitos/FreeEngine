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

	static float Lerp(float start, float end, float percent);

	static float Clamp(float value, float min, float max);

	// Random float between min [inclusive] and max [exclusive]
	static float Random(float min, float max);
	// Random int between min [inclusive] and max [exclusive]
	static int Random(int min, int max);

//Variables
private:
	// Unique instance of the time
	static std::unique_ptr<FMath> _instance;
	static std::once_flag onceFlag;
};

