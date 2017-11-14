#include "Animator.h"
#include "Composite.h"
#include "SpriteAnimator.h"
#include "Debug.h"

Animator::Animator()
{
}

Animator::~Animator()
{
	for (std::vector<Condition*>::iterator it = _allConditions.begin(); it != _allConditions.end(); ++it)
	{
		delete (*it);
	}
	_allConditions.clear();

	for (std::vector<State*>::iterator it = _allState.begin(); it != _allState.end(); ++it)
	{
		delete (*it);
	}
	_allState.clear();
}

void Animator::Awake()
{

}

void Animator::Start()
{
	Condition* c = new Condition();
	c->name = "testTrigger";
	c->type = 3;
	c->conditiontype.t_return = false;
	_allConditions.push_back(c);
	Condition* c2 = new Condition();
	c2->name = "testInt";
	c2->type = 1;
	c2->conditiontype.i_return = 0;
	_allConditions.push_back(c2);

	if (_currentState != nullptr)
	{
		_currentState->OnStateEnter();
	}
}

void Animator::Update(const float deltaTime)
{
	if (_currentState != nullptr)
	{
		_currentState->OnStateUpdate(deltaTime);
		GoToNextState();
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

const void Animator::AddSpriteAnimator(SpriteAnimator* newSpriteAnimator)
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
	if (_currentState->CheckTransition(this) && _currentState->GetNextState() != nullptr)
	{
		_currentState->OnStateExit();
		_currentState = _currentState->GetNextState();
		_currentState->OnStateEnter();
	}
}

void Animator::SetInt(const std::string name, const int value)
{
	for (std::vector<Condition*>::iterator it = _allConditions.begin(); it != _allConditions.end(); ++it)
	{
		if (name == (*it)->name)
		{
			if ((*it)->type == 0)
			{
				Debug::Instance().Print(name + " is not a type int and cannot be set (use SetBool instead) !", DebugMessageType::DEBUGERROR);
			}
			else if ((*it)->type == 1)
			{
				(*it)->conditiontype.i_return = value;
				Debug::Instance().Print(name + " is now set to " + std::to_string(value), DebugMessageType::DEBUGLOG);
			}
			else if ((*it)->type == 2)
			{
				Debug::Instance().Print(name + " is not a type int and cannot be set (use SetFloat instead) !", DebugMessageType::DEBUGERROR);
			}
			else if ((*it)->type == 3)
			{
				Debug::Instance().Print(name + " is not a type int and cannot be set (use SetTrigger instead) !", DebugMessageType::DEBUGERROR);
			}
			return;
		}
	}
	Debug::Instance().Print(name + " is not a valid parameter, be sure it's declared before setting it !", DebugMessageType::DEBUGERROR);
}

void Animator::SetFloat(const std::string name, const float value)
{
	for (std::vector<Condition*>::iterator it = _allConditions.begin(); it != _allConditions.end(); ++it)
	{
		if (name == (*it)->name)
		{
			if ((*it)->type == 0)
			{
				Debug::Instance().Print(name + " is not a type float and cannot be set (use SetBool instead) !", DebugMessageType::DEBUGERROR);
			}
			else if ((*it)->type == 1)
			{
				Debug::Instance().Print(name + " is not a type float and cannot be set (use SetInt instead) !", DebugMessageType::DEBUGERROR);
			}
			else if ((*it)->type == 2)
			{
				(*it)->conditiontype.f_return = value;
				Debug::Instance().Print(name + " is now set to " + std::to_string(value), DebugMessageType::DEBUGLOG);
			}
			else if ((*it)->type == 3)
			{
				Debug::Instance().Print(name + " is not a type float and cannot be set (use SetTrigger instead) !", DebugMessageType::DEBUGERROR);
			}
			return;
		}
	}
	Debug::Instance().Print(name + " is not a valid parameter, be sure it's declared before setting it !", DebugMessageType::DEBUGERROR);
}

void Animator::SetBool(const std::string name, const bool value)
{
	for (std::vector<Condition*>::iterator it = _allConditions.begin(); it != _allConditions.end(); ++it)
	{
		if (name == (*it)->name)
		{
			if ((*it)->type == 0)
			{
				(*it)->conditiontype.b_return = value;
				Debug::Instance().Print(name + " is now set to " + std::to_string(value), DebugMessageType::DEBUGLOG);
			}
			else if ((*it)->type == 1)
			{
				Debug::Instance().Print(name + " is not a type bool and cannot be set (use SetInt instead) !", DebugMessageType::DEBUGERROR);
			}
			else if ((*it)->type == 2)
			{
				Debug::Instance().Print(name + " is not a type bool and cannot be set (use SetFloat instead) !", DebugMessageType::DEBUGERROR);
			}
			else if ((*it)->type == 3)
			{
				Debug::Instance().Print(name + " is not a type bool and cannot be set (use SetTrigger instead) !", DebugMessageType::DEBUGERROR);
			}
			return;
		}
	}
	Debug::Instance().Print(name + " is not a valid parameter, be sure it's declared before setting it !", DebugMessageType::DEBUGERROR);
}


void Animator::SetTrigger(std::string name)
{
	for (std::vector<Condition*>::iterator it = _allConditions.begin(); it != _allConditions.end(); ++it)
	{
		if (name == (*it)->name)
		{
			if ((*it)->type == 0)
			{
				Debug::Instance().Print(name + " is not a type trigger and cannot be set (use SetBool instead) !", DebugMessageType::DEBUGERROR);
			}
			else if ((*it)->type == 1)
			{
				Debug::Instance().Print(name + " is not a type trigger and cannot be set (use SetInt instead) !", DebugMessageType::DEBUGERROR);
			}
			else if ((*it)->type == 2)
			{
				Debug::Instance().Print(name + " is not a type trigger and cannot be set (use SetFloat instead) !", DebugMessageType::DEBUGERROR);
			}
			else if ((*it)->type == 3)
			{
				(*it)->conditiontype.t_return = true;
				Debug::Instance().Print(name + " is now set to true", DebugMessageType::DEBUGLOG);
			}
			return;
		}
	}
	Debug::Instance().Print(name + " is not a valid parameter, be sure it's declared before setting it !", DebugMessageType::DEBUGERROR);
}

const bool Animator::GetBool(const std::string name)
{
	for (std::vector<Condition*>::iterator it = _allConditions.begin(); it != _allConditions.end(); ++it)
	{
		if (name == (*it)->name)
		{
			if ((*it)->type == 0)
			{
				return (*it)->conditiontype.b_return;
			}
			else if ((*it)->type == 1)
			{
				Debug::Instance().Print(name + " is not a type bool and cannot be GET (use GetInt instead)  !", DebugMessageType::DEBUGERROR);
				return false;
			}
			else if ((*it)->type == 2)
			{
				Debug::Instance().Print(name + " is not a type bool and cannot be GET (use GetFloat instead)  !", DebugMessageType::DEBUGERROR);
				return false;
			}
			else if ((*it)->type == 3)
			{
				Debug::Instance().Print(name + " is not a type bool and cannot be GET (use GetTrigger instead)  !", DebugMessageType::DEBUGERROR);
				return false;
			}
		}
	}
	return false;
}

const int Animator::GetInt(const std::string name)
{
	for (std::vector<Condition*>::iterator it = _allConditions.begin(); it != _allConditions.end(); ++it)
	{
		if (name == (*it)->name)
		{
			if ((*it)->type == 0)
			{
				Debug::Instance().Print(name + " is not a type int and cannot be GET (use GetBool instead) !", DebugMessageType::DEBUGERROR);
			}
			else if ((*it)->type == 1)
			{
				return (*it)->conditiontype.i_return;
			}
			else if ((*it)->type == 2)
			{
				Debug::Instance().Print(name + " is not a type int and cannot be GET (use GetFloat instead)  !", DebugMessageType::DEBUGERROR);
			}
			else if ((*it)->type == 3)
			{
				Debug::Instance().Print(name + " is not a type int and cannot be GET (use GetTrigger instead)  !", DebugMessageType::DEBUGERROR);
			}
			return -1;
		}
	}
	return -1;
}

const float Animator::GetFloat(const std::string name)
{
	for (std::vector<Condition*>::iterator it = _allConditions.begin(); it != _allConditions.end(); ++it)
	{
		if (name == (*it)->name)
		{
			if ((*it)->type == 0)
			{
				Debug::Instance().Print(name + " is not a type float and cannot be GET (use GetBool instead)  !", DebugMessageType::DEBUGERROR);
			}
			else if ((*it)->type == 1)
			{
				Debug::Instance().Print(name + " is not a type float and cannot be GET (use GetInt instead)  !", DebugMessageType::DEBUGERROR);
			}
			else if ((*it)->type == 2)
			{
				return (*it)->conditiontype.f_return;
			}
			else if ((*it)->type == 3)
			{
				Debug::Instance().Print(name + " is not a type float and cannot be GET (use GetTrigger instead)  !", DebugMessageType::DEBUGERROR);
			}
			return -1;
		}
	}
	return -1;
}

const bool Animator::GetTrigger(const std::string name)
{
	for (std::vector<Condition*>::iterator it = _allConditions.begin(); it != _allConditions.end(); ++it)
	{
		if (name == (*it)->name)
		{
			if ((*it)->type == 0)
			{
				Debug::Instance().Print(name + " is not a type trigger and cannot be GET (use GetBool instead)  !", DebugMessageType::DEBUGERROR);
			}
			else if ((*it)->type == 1)
			{
				Debug::Instance().Print(name + " is not a type trigger and cannot be GET (use GetInt instead)  !", DebugMessageType::DEBUGERROR);
			}
			else if ((*it)->type == 2)
			{
				Debug::Instance().Print(name + " is not a type trigger and cannot be GET (use GetFloat instead)  !", DebugMessageType::DEBUGERROR);
				return false;
			}
			else if ((*it)->type == 3)
			{
				bool toReturn = (*it)->conditiontype.t_return;
				if (toReturn == true)
					(*it)->conditiontype.t_return = false;
				return toReturn;
			}
			return false;
		}
	}
	return false;
}