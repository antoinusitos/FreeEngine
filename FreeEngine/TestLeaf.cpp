#include "TestLeaf.h"
#include "Debug.h"
#include "Input.h"
#include "GamepadManager.h"
#include "Composite.h"
#include "EditorManager.h"

TestLeaf::TestLeaf()
{
}

TestLeaf::~TestLeaf()
{
}

void TestLeaf::Awake()
{
	Debug::Instance().Print("Awake test leaf", DebugMessageType::DEBUGLOG);
}

void TestLeaf::Start()
{
	Debug::Instance().Print("Start test leaf", DebugMessageType::DEBUGLOG);
}

void TestLeaf::Update(const float deltaTime)
{
	if (EditorManager::Instance().GetCurrentState() == EditorState::EDITING) return;

	if (Input::Instance().GetKeyPressed(KEYCODE::ARROWRIGHT) || GamepadManager::Instance().GetLeftStickX(_playerNumber) >= 0.25f)
	{
		_parent->transform.position.x += deltaTime * 200.0f;
	}
	if (Input::Instance().GetKeyPressed(KEYCODE::ARROWLEFT) || GamepadManager::Instance().GetLeftStickX(_playerNumber) <= -0.25f)
		_parent->transform.position.x -= deltaTime * 200.0f;
}

void TestLeaf::Exit()
{
	Debug::Instance().Print("Exit test leaf", DebugMessageType::DEBUGLOG);
}

void TestLeaf::Render(sf::RenderWindow* window)
{
}

void TestLeaf::SetPlayerNumber(int newNumber)
{
	_playerNumber = newNumber;
}