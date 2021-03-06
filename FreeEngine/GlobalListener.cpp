#include "GlobalListener.h"

std::unique_ptr<GlobalListener> GlobalListener::_instance;
std::once_flag GlobalListener::onceFlag;

GlobalListener::GlobalListener()
{
	_listener = sf::Listener();
	_listener.setUpVector(0, 1, 0); 
	_listener.setPosition(0, 0, 0);
	_listener.setDirection(1.f, 0.f, 0.f);
	_listener.setGlobalVolume(100);
}

GlobalListener::~GlobalListener()
{
}

void GlobalListener::SetPosition(const float x, const float y)
{
	_listener.setPosition(x, y, 0);
}

void GlobalListener::SetGlobalVolume(const float volume)
{
	_listener.setGlobalVolume(volume);
}