#include "Animator.h"
#include "Composite.h"
#include "SpriteAnimator.h"

Animator::Animator()
{
}

Animator::~Animator()
{
}

void Animator::Awake()
{

}

void Animator::Start()
{
	if (_currentState != nullptr)
	{
		_currentState->OnStateEnter();
	}
}

void Animator::Update(float deltaTime)
{
	if (_currentState != nullptr)
	{
		_currentState->OnStateUpdate(deltaTime);
	}
}

void Animator::Render(sf::RenderWindow* window)
{
	if (_currentState != nullptr)
	{
		_currentState->OnStateRender(window);
	}
}

void Animator::Exit()
{

}

void Animator::AddSpriteAnimator(SpriteAnimator* newSpriteAnimator)
{
	State* newState = new State("NewState");
	newState->SetSpriteAnimator(newSpriteAnimator);
	AddNewState(newState);
}

void Animator::AddNewState(State* newState)
{
	_allState.push_back(newState);
	if ((int)_allState.size() == 1)
	{
		_currentState = newState;
	}
}

void Animator::GoToNextState()
{
	if (_currentState->GetNextState() != nullptr)
	{
		_currentState->OnStateExit();
		_currentState = _currentState->GetNextState();
		_currentState->OnStateEnter();
	}
}