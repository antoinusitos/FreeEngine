#include "Window.h"
#include "DebugWindowLayout.h"
#include "WindowLayout.h"
#include "Engine.h"

#define FULLSCREEN false

std::unique_ptr<Window> Window::_instance;
std::once_flag Window::onceFlag;

Window::Window()
{
	
}

Window::~Window()
{
}

sf::RenderWindow* Window::GetWindow()
{
	return _window.get();
}

void Window::Init()
{
#if FULLSCREEN
	_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "Free Engine", sf::Style::Fullscreen);
#else
	_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "Free Engine"/*, sf::Style::Fullscreen*/);
#endif
}

void Window::InitInternalWindows()
{
	dwl = std::make_unique<DebugWindowLayout>();
	dwl->Init();
}

void Window::Exit()
{
	_window->close();
	dwl.release();
}

void Window::Render()
{
	_window->clear(sf::Color::Black);
	for (std::vector<WindowLayout*>::iterator it = _allWindowLayout.begin(); it != _allWindowLayout.end(); ++it)
	{
		(*it)->Render(_window.get());
	}
	_window->display();
}

void Window::AddRenderingLayout(WindowLayout* newLayout)
{
	_allWindowLayout.push_back(newLayout);
}

void Window::RemoveRenderingLayout(WindowLayout* layoutToRemove)
{
	int index = -1;
	bool found = false;

	for (std::vector<WindowLayout*>::iterator it = _allWindowLayout.begin(); it != _allWindowLayout.end(); ++it)
	{
		index++;
		if (layoutToRemove == (*it))
		{
			found = true;
		}
	}

	if (found)
	{
		_allWindowLayout.erase(_allWindowLayout.begin() + index);
	}
}

void Window::RemoveAllRendering()
{
	_allWindowLayout.erase(_allWindowLayout.begin(), _allWindowLayout.end());
}

DebugWindowLayout* Window::GetDebugWindowLayout()
{
	return dwl.get();
}
