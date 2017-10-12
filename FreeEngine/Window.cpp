#include "Window.h"

Window* Window::_instance = NULL;

Window::Window()
{
	
}

Window::~Window()
{
}

sf::Window* Window::GetWindow()
{
	return _window;
}

void Window::Init()
{
	_window = new sf::RenderWindow(sf::VideoMode(800, 600), "Free Engine");
}

void Window::Exit()
{
	_window->close();
}

void Window::Render()
{
	_window->clear(sf::Color::Black);
	_window->display();
}