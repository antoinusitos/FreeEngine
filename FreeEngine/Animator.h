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
	void Update(const float deltaTime);
	void Exit();
	void Awake();
	const void Render(sf::RenderWindow* window);

	const void AddSpriteAnimator(SpriteAnimator* newSpriteAnimator);
	void AddNewState(State* newState);
	void GoToNextState();

	void SetInt(const std::string name, const int value);
	void SetFloat(const std::string name, const float value);
	void SetBool(const std::string name, const bool value);
	void SetTrigger(const std::string name);

	const bool GetBool(const std::string name);
	const int GetInt(const std::string name);
	const float GetFloat(const std::string name);
	const bool GetTrigger(const std::string name);

private:
	std::vector<State*> _allState;
	std::vector<Condition*> _allConditions;
	State* _currentState;
};

