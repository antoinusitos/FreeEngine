#pragma once

#include <map>

class FCurve
{
public:
	FCurve();
	~FCurve();

	void InsertTiming(float time, float value);

	float GetValue(float time);

private:
	std::map<float,float> _allKey;

	//TODO : do multiple type of curve 
};

