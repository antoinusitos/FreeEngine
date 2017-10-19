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
	for (std::vector<sf::Drawable*>::iterator it = _allDrawable.begin(); it != _allDrawable.end(); ++it)
	{
		SFMLWindow->draw((**it));
	}
}

void WindowLayout::AddToRendering()
{
	Window::Instance().AddRenderingLayout(this);
}

void WindowLayout::UnregisterToRendering()
{
	Window::Instance().RemoveRenderingLayout(this);
}