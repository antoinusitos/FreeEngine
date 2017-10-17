#include "WindowLayout.h"
#include "Window.h"

WindowLayout::WindowLayout()
{
}

WindowLayout::~WindowLayout()
{
}

void WindowLayout::Render(std::shared_ptr<sf::RenderWindow> SFMLWindow)
{
	for (std::vector<std::shared_ptr<sf::Drawable>>::iterator it = _allDrawable.begin(); it != _allDrawable.end(); ++it)
	{
		SFMLWindow->draw((**it));
	}
}

void WindowLayout::AddToRendering()
{
	Window::Instance().AddRenderingLayout(this);
}