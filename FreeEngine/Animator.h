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

private:
	std::vector<State*> _allState;
	State* _currentState;
};

