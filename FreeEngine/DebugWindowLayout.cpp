#include "DebugWindowLayout.h"
#include "Window.h"
#include "Debug.h"
#include "ResourcesManager.h"

DebugWindowLayout::DebugWindowLayout()
{
	font = ResourcesManager::Instance().GetFont("arial.ttf");
	_active = false;
}

DebugWindowLayout::~DebugWindowLayout()
{
}

void DebugWindowLayout::Init()
{
	FileHandler::Instance().RegisterNewWatcher(this, "FreeEngine/Assets/Config/Engine.txt");

	_background = sf::RectangleShape(sf::Vector2f((float)Window::Instance().GetWindow()->getSize().x, _debugZoneSizeY));
	_background.setFillColor(sf::Color(150, 150, 150));
	_background.setPosition(0, Window::Instance().GetWindow()->getSize().y - _debugZoneSizeY);
	_allDrawable.push_back(&_background);

	_beginY = _background.getPosition().y;
	_beginX = _background.getPosition().x + 5;
       
	Window::Instance().AddRenderingLayout(this);
}

void DebugWindowLayout::Unregister()
{
	Window::Instance().RemoveRenderingLayout(this);
}

void DebugWindowLayout::AddString(DebugMessage debugMessage)
{
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(15);
	text.setString(debugMessage.message);
	switch (debugMessage.messageType)
	{
	case DebugMessageType::DEBUGLOG :
		text.setFillColor(sf::Color::Black);
		break;

	case DebugMessageType::DEBUGERROR :
		text.setFillColor(sf::Color::Red);
		break;

	case DebugMessageType::DEBUGWARNING :
		text.setFillColor(sf::Color::Yellow);
		break;
		 
	default:
		text.setFillColor(sf::Color::Black);
		break;
	}
	text.setPosition(_beginX, _beginY + _index * _incrementingY);
	_allText.push_back(text);
	_index++;
}

void DebugWindowLayout::Render(sf::RenderWindow* SFMLWindow)
{
	WindowLayout::Render(SFMLWindow);

	if (_active)
	{
		int tempIndex = 0;
		int startingIndex = 0;

		int size = _allText.size();
		if (size > _numberLogInConsole)
		{
			startingIndex = size - _numberLogInConsole;
		}

		for (std::vector<sf::Text>::iterator it = _allText.begin() + startingIndex; it != _allText.end(); ++it)
		{
			(*it).setPosition(_beginX, _beginY + tempIndex * _incrementingY);
			SFMLWindow->draw((*it));
			tempIndex++;
		}
	}
}

void DebugWindowLayout::Update(float deltaTime)
{
	if (_opening)
	{
	
	}
	else
	{

	}
}

void DebugWindowLayout::NotifyChange()
{
	bool readable = false;
	std::string allLines = FileHandler::Instance().ReadFile(configFileName, &readable);

	if (readable)
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

void DebugWindowLayout::HandleDataChanges()
{
	for (std::vector<EngineData>::iterator it = _allEngineData.begin(); it != _allEngineData.end(); ++it)
	{
		//std::cout << "category:" << (it)->category << " || value:" << (it)->value << '\n';
		std::string tempCat = (it)->category.c_str();
		std::string tempVal = (it)->value.c_str();

		if (tempCat == "ConsoleSpeed")
		{
			_consoleSpeed = atof(tempVal.c_str());
		}
		else if (tempCat == "ConsoleHeight")
		{
			_debugZoneSizeY = atof(tempVal.c_str());
		}
		else if (tempCat == "ConsoleColor")
		{
			std::string delimiter = ",";
			size_t pos = 0;
			std::string token;
			float color[3] = { 0 };
			int index = 0;

			while ((pos = tempVal.find(delimiter)) != std::string::npos) {
				token = tempVal.substr(0, pos);
				color[index] = atof(token.c_str());
				tempVal.erase(0, pos + delimiter.length());
				index++;
			}
			token = tempVal;
			color[index] = atof(token.c_str());

			_color = FVector3(color[0], color[1], color[2]);
			_background.setFillColor(sf::Color(_color.x, _color.y, _color.z));
		}
	}
}