#include "ToolBarButton.h"
#include "Input.h"

ToolBarButton::ToolBarButton()
{

}

ToolBarButton::~ToolBarButton()
{
}

void ToolBarButton::UpdateButton(float deltaTime)
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
			Execute();
		}
	}
	else
	{
		//std::cout << "mouse pos x=" << Input::Instance().GetMousePosition().x  << " y=" << Input::Instance().GetMousePosition().y << '\n';
	}
}

void ToolBarButton::SetPosition(float x, float y)
{
	_position.x = x;
	_position.y = y;
	_text.setPosition(x, y);
}

void ToolBarButton::SetSize(float x, float y)
{
	_size.x = x;
	_size.y = y;
}

void ToolBarButton::Render(sf::RenderWindow* SFMLWindow)
{
	SFMLWindow->draw(_text);
}

void ToolBarButton::SetName(std::string newName)
{
	_name = newName;
	_text.setFont(_font);
	_text.setScale(.5f, .5f);
	_text.setString(newName);
}

void ToolBarButton::SetFont(sf::Font newFont)
{
	_font = newFont;
}