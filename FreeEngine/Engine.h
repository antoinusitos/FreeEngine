#pragma once

class Engine
{
public:
	Engine();
	~Engine();

	void Update();

	void Launch();

private :
	bool _isRunning = false;
};

