#pragma once

#include "SFML\Graphics.hpp"

class SpriteAnimator;

class State
{
public:
	class Transition
	{
	public:
		State* newState;

		Transition::Transition()
		{

		}

		Transition::~Transition()
		{

		}
	};

	State(std::string newName);
	~State();

	void OnStateEnter();

	void OnStateUpdate(float deltaTime);

	void OnStateRender(sf::RenderWindow* window);

	void OnStateExit();

	void SetSpriteAnimator(SpriteAnimator* newSpriteAnimator);

	void SetTransition(State* newState);

	State* GetNextState();

private:
	SpriteAnimator* _spriteAnimator;

	std::string _name;

	Transition* _transition;
};

