#include "Window.h"
#include "DebugWindowLayout.h"

Window* Window::_instance = NULL;

Window::Window()
{
	
}

Window::~Window()
{
}

sf::RenderWindow* Window::GetWindow()
{
	return _window;
}

void Window::Init()
{
	_window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Free Engine", sf::Style::Fullscreen);

	DebugWindowLayout* dwl = new DebugWindowLayout();
}

void Window::Exit()
{
	_window->close();
}

void Window::Render()
{
	_window->clear(sf::Color::Black);
	for (std::vector<WindowLayout*>::iterator it = _allWindowLayout.begin(); it != _allWindowLayout.end(); ++it)
	{
		(*it)->Render(_window);
	}
	_window->display();
}

void Window::AddRenderingLayout(WindowLayout* newLayout)
{
	_allWindowLayout.push_back(newLayout);
}