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
	FileHandler::Instance().RegisterNewWatcher(this, "FreeEngine/Assets/Config/Engine.txt");

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

void Window::NotifyChange()
{
	bool readable = false;
	std::string allLines = FileHandler::Instance().ReadFile(configFileName, &readable);

	if(readable)
	{
		std::cout << "file : " << configFileName << " changed !" << '\n';

		std::string delimiter = "\n";
		std::string delimiterCategory = "=";

		size_t pos = 0;
		std::string token;
		while ((pos = allLines.find(delimiter)) != std::string::npos) {
			token = allLines.substr(0, pos);
			if (token[0] != '#')
			{
				std::string category = token.substr(0, token.find(delimiterCategory));
				size_t posTemp = token.find(delimiterCategory);
				token.erase(0, posTemp + delimiterCategory.length());
				std::string value = token;
				EngineData data = EngineData();
				data.category = category;
				data.value = value;
				_allEngineData.push_back(data);
			}
			allLines.erase(0, pos + delimiter.length());
		}

		HandleDataChanges();
	}
	else
	{
		Debug::Instance().Print("Cannot open file : " + configFileName);
	}
}

void Window::HandleDataChanges()
{
	for (std::vector<EngineData>::iterator it = _allEngineData.begin(); it != _allEngineData.end(); ++it)
	{
		std::cout << "category:" << (it)->category << " || value:" << (it)->value << '\n';
		std::string tempCat = (it)->category.c_str();
		std::string tempVal = (it)->value.c_str();

		if (tempCat == "Resolution")
		{
			std::string delimiter = "x";
			std::string x = tempVal.substr(0, tempVal.find(delimiter));
			size_t posTemp = tempVal.find(delimiter);
			tempVal.erase(0, posTemp + delimiter.length());
			std::string y = tempVal;

			unsigned int dimX = atoi(x.c_str());
			unsigned int dimY = atoi(y.c_str());

			sf::Vector2u vec = sf::Vector2u(dimX, dimY);
			_window.get()->setSize(vec);

			std::cout << "Set new Size to " << dimX << "x" << dimY << '\n';
		}
	}
}