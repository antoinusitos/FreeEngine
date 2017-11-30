#pragma once

#include <memory>
#include <mutex>
#include "FVector3.h"

class ScreenShakeManager
{
public:
	ScreenShakeManager();
	~ScreenShakeManager();

	// Get a unique instance of the time
	static ScreenShakeManager& ScreenShakeManager::Instance()
	{
		std::call_once(ScreenShakeManager::onceFlag, []() {
			_instance.reset(new ScreenShakeManager);
		});

		return *(_instance.get());
	}

	void ShakeForSeconds(float strenght, float time = 1.0f, float repetition = 0.1f);

	void Update(float deltaTime);

private:
	// Unique instance of the time
	static std::unique_ptr<ScreenShakeManager> _instance;
	static std::once_flag onceFlag;

	float _timeToShake = 0;
	float _currentTimeShaking = 0;
	float _strenght = 0;
	float _currentProgression = 0;
	float _repetition = 0.1f;
	float _speed = 50.0f;
	bool _isShaking = false;

	FVector3 _offset = FVector3();
	FVector3 _lastOffset = FVector3();
	FVector3 _currentOffset = FVector3();
};