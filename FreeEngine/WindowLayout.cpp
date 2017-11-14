#include "WindowLayout.h"
#include "Window.h"

WindowLayout::WindowLayout()
{
}

WindowLayout::~WindowLayout()
{
}

void WindowLayout::Render(sf::RenderWindow* SFMLWindow)
{
	if (_active)
	{
		for (std::vector<sf::Drawable*>::iterator it = _allDrawable.begin(); it != _allDrawable.end(); ++it)
		{
			SFMLWindow->draw((**it));
		}
	}
}

void WindowLayout::Update(const float deltaTime)
{

}

void WindowLayout::AddToRendering()
{
	Window::Instance().AddRenderingLayout(this);
}

void WindowLayout::UnregisterToRendering()
{
	Window::Instance().RemoveRenderingLayout(this);
}

void WindowLayout::SetVisibility(const bool newVisibility)
{
	_active = newVisibility;
}