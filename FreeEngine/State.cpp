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
	delete _spriteAnimator;
	delete _transition;
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
		for (std::vector<Condition*>::iterator it = _transition->conditions.begin(); it != _transition->conditions.end(); ++it)
		{
			if ((*it)->type == 0)
			{
				if(anim->GetBool((*it)->name) != (*it)->conditiontype.b_return)
					return false;
			}
			else if ((*it)->type == 1)
			{
				if(anim->GetInt((*it)->name) != (*it)->conditiontype.i_return)
					return false;
			}
			else if ((*it)->type == 2)
			{
				if(anim->GetFloat((*it)->name) != (*it)->conditiontype.f_return)
					return false;
			}
			else if ((*it)->type == 3)
			{
				if (anim->GetTrigger((*it)->name) != true)
					return false;
			}
		}
		return true;
	}
	return false;
}