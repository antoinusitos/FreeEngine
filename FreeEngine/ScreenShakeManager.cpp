#include "ScreenShakeManager.h"
#include "CameraManager.h"
#include "FMath.h"

std::unique_ptr<ScreenShakeManager> ScreenShakeManager::_instance;
std::once_flag ScreenShakeManager::onceFlag;

ScreenShakeManager::ScreenShakeManager()
{

}

ScreenShakeManager::~ScreenShakeManager()
{

}

void ScreenShakeManager::ShakeForSeconds(float strenght, float time, float repetition)
{
	_isShaking = true;
	_timeToShake = time;
	_currentTimeShaking = 0;
	_strenght = strenght;

	_currentProgression = 0;
	_lastOffset = FVector3();
	_offset = FVector3(FMath::Random(-strenght / 2.0f, strenght / 2.0f), FMath::Random(-strenght / 2.0f, strenght / 2.0f), 0.0f);
	_currentOffset = FVector3();
}

void ScreenShakeManager::Update(float deltaTime)
{
	if (_isShaking)
	{
		_currentTimeShaking += deltaTime;

		if (_currentTimeShaking >= _timeToShake)
		{
			_isShaking = false;
			_currentProgression = 0;
		}

		_currentProgression += deltaTime;
		if (_currentProgression >= _repetition)
		{
			_currentProgression = 0;
			_currentOffset = FVector3(FMath::Random(-_strenght / 2.0f, _strenght / 2.0f), FMath::Random(-_strenght / 2.0f, _strenght / 2.0f), 0.0f);
		}
	}
	else
	{
		_currentProgression += deltaTime * _speed;
		_currentOffset.x = FMath::Lerp(_lastOffset.x, 0, _currentProgression);
		_currentOffset.y = FMath::Lerp(_lastOffset.y, 0, _currentProgression);
	}

	CameraManager::Instance().SetLocalOffset(_currentOffset);
}