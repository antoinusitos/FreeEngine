#include "FCurve.h"
#include "FMath.h"

FCurve::FCurve()
{
	_allKey.insert(std::pair<float, float>(0, 0));
	_allKey.insert(std::pair<float, float>(1, 0));
}

FCurve::~FCurve()
{
}

void FCurve::InsertTiming(float time, float value)
{
	std::map<float, float>::iterator it;
	it = _allKey.find(time);
	if (it != _allKey.end())
	{
		_allKey.at(time) = value;
	}
	else
	{
		_allKey.insert(std::pair<float, float>(time, value));
	}
}

float FCurve::GetValue(float time)
{
	time = FMath::Clamp01(time);

	float timeUnder = 0;
	float valueUnder = 0;
	float timeAbove = 1;
	float valueAbove = 0;

	for (auto& x : _allKey) {
		if (x.first == time) return x.second;

		if (x.first < time)
		{
			timeUnder = x.first;
			valueUnder = x.second;
		}
		else if (x.first > time && x.first < timeAbove)
		{
			timeAbove = x.first;
			valueAbove = x.second;
		}
	}

	float percentage = FMath::Map(time, timeUnder, timeAbove, 0.0f, 1.0f);
	return FMath::Lerp(valueUnder, valueAbove, percentage);

}