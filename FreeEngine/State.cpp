#include "State.h"
#include "Debug.h"
#include "SpriteAnimator.h"
#include "Animator.h"
#include "Transition.h"

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

void State::SetTransition(State* newState, Transition* newTransition)
{
	_transition = newTransition;
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

bool State::CheckTransition(Animator* anim)
{
	if (_transition != nullptr)
	{
		if (_transition->condition.type == 0)
		{
			return anim->GetBool(_transition->condition.name) == _transition->condition.conditiontype.b_return;
		}
		else if (_transition->condition.type == 1)
		{
			return anim->GetInt(_transition->condition.name) == _transition->condition.conditiontype.i_return;
		}
		else if (_transition->condition.type == 2)
		{
			return anim->GetFloat(_transition->condition.name) == _transition->condition.conditiontype.f_return;
		}
	}
	return false;
}