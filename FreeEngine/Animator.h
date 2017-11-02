#pragma once

#include "Leaf.h"
#include <vector>
#include "State.h"

class SpriteAnimator;

class Animator : public Leaf
{
public:
	Animator();
	~Animator();

	void Start();
	void Update(float deltaTime);
	void Exit();
	void Awake();
	void Render(sf::RenderWindow* window);

	void AddNewState(State* newState);
	void AddSpriteAnimator(SpriteAnimator* newSpriteAnimator);
	void GoToNextState();

	void SetInt(std::string name, int value);
	void SetFloat(std::string name, float value);
	void SetBool(std::string name, bool value);
	void SetTrigger(std::string name);

	bool GetBool(std::string name);
	int GetInt(std::string name);
	float GetFloat(std::string name);
	bool GetTrigger(std::string name);

private:
	std::vector<State*> _allState;
	std::vector<Condition*> _allConditions;
	State* _currentState;
};

