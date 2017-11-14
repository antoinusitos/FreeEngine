#include "ToolBarButton.h"
#include "Input.h"

ToolBarButton::ToolBarButton()
{
	_active = false;
}

ToolBarButton::~ToolBarButton()
{
}

void ToolBarButton::UpdateButton(const float deltaTime)
{
	if (
		Input::Instance().GetMousePosition().x > _position.x &&
		Input::Instance().GetMousePosition().x < _position.x + _size.x &&
		Input::Instance().GetMousePosition().y > _position.y &&
		Input::Instance().GetMousePosition().y < _position.y + _size.y
		)
	{
		//std::cout << "mouse inside tool bar button " << _name << '\n';
		if (Input::Instance().GetKeyDown(KEYCODE::MOUSELEFT))
		{
			// if we are a parent button
			if ((int)_subButtons.size() > 0)
			{
				if (!_active)
				{
					SetActive(true);
					Execute();
				}
				else
				{
					SetActive(false);
				}
			}
			//if we are a child
			else
			{
				Execute();
			}
		}
	}
	else
	{
		//std::cout << "mouse pos x=" << Input::Instance().GetMousePosition().x  << " y=" << Input::Instance().GetMousePosition().y << '\n';
	}

	if (_active)
	{
		for (std::vector<ToolBarButton*>::iterator it = _subButtons.begin(); it != _subButtons.end(); ++it)
		{
			(*it)->UpdateButton(deltaTime);
		}
	}
}

void ToolBarButton::SetPosition(const float x, const float y)
{
	_position.x = x;
	_position.y = y;
	_text.setPosition(x, y);
	_background.setPosition(x, y);
}

void ToolBarButton::SetPosition(const FVector2& position)
{
	_position.x = position.x;
	_position.y = position.y;
	_text.setPosition(position.x, position.y);
	_background.setPosition(position.x, position.y);
}

void ToolBarButton::SetSize(const float x, const float y)
{
	_size.x = x;
	_size.y = y;
	_background.setSize(sf::Vector2f(x, y));
}

void ToolBarButton::SetSize(const FVector2& size)
{
	_size.x = size.x;
	_size.y = size.y;
	_background.setSize(sf::Vector2f(size.x, size.y));
}

void ToolBarButton::Render(sf::RenderWindow* SFMLWindow)
{
	SFMLWindow->draw(_background);
	SFMLWindow->draw(_text);
	if (_active)
	{
		for (std::vector<ToolBarButton*>::iterator it = _subButtons.begin(); it != _subButtons.end(); ++it)
		{
			(*it)->Render(SFMLWindow);
		}
	}
}

void ToolBarButton::SetName(const std::string newName)
{
	_name = newName;
	_text.setFont(_font);
	_text.setScale(.5f, .5f);
	_text.setString(newName);
}

void ToolBarButton::SetFont(const sf::Font newFont)
{
	_font = newFont;
	for (std::vector<ToolBarButton*>::iterator it = _subButtons.begin(); it != _subButtons.end(); ++it)
	{
		(*it)->SetFont(newFont);
	}
}

void ToolBarButton::InitBackground()
{
	_background = sf::RectangleShape(sf::Vector2f(0, 0));
	_background.setFillColor(sf::Color(80, 80, 80));
	_background.setPosition(0, 0);
}

void ToolBarButton::SetActive(const bool newState)
{
	_active = newState;
	for (std::vector<ToolBarButton*>::iterator it = _subButtons.begin(); it != _subButtons.end(); ++it)
	{
		(*it)->SetActive(newState);
	}
}

void ToolBarButton::SetParent(ToolBarButton* newParent)
{
	_parent = newParent;
}

const ToolBarButton* ToolBarButton::GetParent()
{
	return _parent;
}