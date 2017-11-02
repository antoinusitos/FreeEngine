#pragma once

#include "SFML\Graphics.hpp"

class SpriteAnimator;
class Animator;
class Transition;

class State
{
public:

	State(std::string newName);
	~State();

	void OnStateEnter();

	void OnStateUpdate(float deltaTime);

	void OnStateRender(sf::RenderWindow* window);

	void OnStateExit();

	void SetSpriteAnimator(SpriteAnimator* newSpriteAnimator);

	void SetTransition(State* newState, Transition* newTransition);

	bool CheckTransition(Animator* anim);

	State* GetNextState();

private:
	SpriteAnimator* _spriteAnimator;

	std::string _name;

	Transition* _transition;
};

