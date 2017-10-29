#include "Window.h"
#include "DebugWindowLayout.h"
#include "WindowLayout.h"
#include "Engine.h"

const bool STARTFULLSCREEN = false;

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
#if STARTFULLSCREEN
	_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "Free Engine", sf::Style::Fullscreen);
	_screenType = ScreenType::FULLSCREEN;
#else
	_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "Free Engine");
	_screenType = ScreenType::WINDOWED;
#endif

	//InitInternalWindows();
}

void Window::InitInternalWindows()
{
	FileHandler::Instance().RegisterNewWatcher(this, "FreeEngine/Assets/Config/Engine.txt");

	dwl = std::make_unique<DebugWindowLayout>();
	dwl->Init();

	Debug::Instance().SetDebugWindow(GetDebugWindowLayout());
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
		_allEngineData.erase(_allEngineData.begin(), _allEngineData.end());

		Debug::Instance().Print("file : " + configFileName + " changed !\n", DebugMessageType::DEBUGWARNING);

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
		Debug::Instance().Print("Cannot open file : " + configFileName, DebugMessageType::DEBUGERROR);
	}
}

void Window::HandleDataChanges()
{
	for (std::vector<EngineData>::iterator it = _allEngineData.begin(); it != _allEngineData.end(); ++it)
	{
		//std::cout << "category:" << (it)->category << " || value:" << (it)->value << '\n';
		std::string tempCat = (it)->category.c_str();
		std::string tempVal = (it)->value.c_str();

		if (tempCat == "FullScreenResolution")
		{
			if (_screenType == ScreenType::FULLSCREEN)
			{
				std::string x;
				std::string y;
				GetResolutionValuesWithDelimiter(tempVal, "x", x, y);

				_screenResolutionX = atoi(x.c_str());
				_screenResolutionY = atoi(y.c_str());

				SetResolutionScreen(_screenResolutionX, _screenResolutionY, 0, 0);
			}
		}
		else if (tempCat == "Resolution")
		{
			if (_screenType == ScreenType::WINDOWED)
			{
				std::string x;
				std::string y;
				GetResolutionValuesWithDelimiter(tempVal, "x", x, y);

				_screenResolutionX = atoi(x.c_str());
				_screenResolutionY = atoi(y.c_str());

				sf::Vector2u size = _window.get()->getSize();
				SetResolutionScreen(_screenResolutionX, _screenResolutionY, size.x / 2, size.y / 2);
			}
		}
		else if (tempCat == "Sceen")
		{
			if (tempVal == "FULLSCREEN" && _screenType == ScreenType::WINDOWED)
			{
				_window.get()->close();
				_window.release();
				_screenType = ScreenType::FULLSCREEN;
				SetScreenType(_screenType);
			}
			else if (tempVal == "WINDOWED" && _screenType == ScreenType::FULLSCREEN)
			{
				_window.get()->close();
				_window.release();
				_screenType = ScreenType::WINDOWED;
				SetScreenType(_screenType);
			}
		}
	}
}

void Window::SetResolutionScreen(int X, int Y, int posX, int posY)
{
	sf::Vector2u vec = sf::Vector2u(X, Y);
	_window.get()->setSize(vec);

	_window->setPosition(sf::Vector2i(posX, posY));

	std::string debug = "Set new Size to windowed " + std::to_string(X) + "x" + std::to_string(Y) + '\n';
	Debug::Instance().Print(debug, DebugMessageType::DEBUGLOG);
}

void Window::SetScreenType(ScreenType newType)
{
	switch (newType)
	{
	case ScreenType::FULLSCREEN :
		_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "Free Engine", sf::Style::Fullscreen);
		_window->setPosition(sf::Vector2i(0, 0));
		break;

	case ScreenType::WINDOWED :
		_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1920, 1080), "Free Engine");
		sf::Vector2u size = _window.get()->getSize();
		_window->setPosition(sf::Vector2i(size.x / 2, size.y / 2));
		break;
	}
}

void Window::GetResolutionValuesWithDelimiter(std::string& text, std::string delimiter, std::string& x, std::string& y)
{
	x = text.substr(0, text.find(delimiter));
	size_t posTemp = text.find(delimiter);
	text.erase(0, posTemp + delimiter.length());
	y = text;
}

float Window::GetScreenResolutionX()
{
	return _screenResolutionX;
}

float Window::GetScreenResolutionY()
{
	return _screenResolutionY;
}

void Window::SetView(sf::View newView)
{
	_window->setView(newView);
}