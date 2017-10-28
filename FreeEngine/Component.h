#pragma once
class Component
{
public:
	Component();
	~Component();

	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void Exit();
	virtual void Awake();
	virtual void Render();

	bool isActive = true;
};

