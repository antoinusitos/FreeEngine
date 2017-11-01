#include "State.h"
#include "Debug.h"
#include "SpriteAnimator.h"

State::State(std::string newName)
{
	_name = newName;
}

State::~State()
{
}

void State::OnStateEnter()
{
	if (_spriteAnimator == nullptr)
	{
		Debug::Instance().Print("No sprite animator for state " + _name, DebugMessageType::DEBUGERROR);
	}
	else
		Debug::Instance().Print("Enter state " + _name, DebugMessageType::DEBUGLOG);
}

void State::OnStateUpdate(float deltaTime)
{
	if (_spriteAnimator != nullptr)
	{
		_spriteAnimator->Update(deltaTime);
	}
}

void State::OnStateRender(sf::RenderWindow* window)
{
	if (_spriteAnimator != nullptr)
	{
		_spriteAnimator->Render(window);
	}
}

void State::OnStateExit()
{
	Debug::Instance().Print("Leaving state " + _name, DebugMessageType::DEBUGLOG);
}

void State::SetSpriteAnimator(SpriteAnimator* newSpriteAnimator)
{
	_spriteAnimator = newSpriteAnimator;
}

void State::SetTransition(State* newState)
{
	if (_transition == nullptr)
	{
		_transition = new Transition();
	}
	_transition->newState = newState;
}

State* State::GetNextState()
{
	if (_transition != nullptr)
	{
		return _transition->newState;
	}
	return nullptr;
}