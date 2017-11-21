#include "TestLeaf.h"
#include "Debug.h"
#include "Input.h"
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
	//std::cout << "Update test leaf" << '\n';

	if (EditorManager::Instance().GetCurrentState() == EditorState::EDITING) return;

	if (Input::Instance().GetKeyPressed(KEYCODE::ARROWRIGHT))
		_parent->transform.position.x += deltaTime * 200.0f;
	if (Input::Instance().GetKeyPressed(KEYCODE::ARROWLEFT))
		_parent->transform.position.x -= deltaTime * 200.0f;
}

void TestLeaf::Exit()
{
	Debug::Instance().Print("Exit test leaf", DebugMessageType::DEBUGLOG);
}

void TestLeaf::Render(sf::RenderWindow* window)
{
	//std::cout << "Render test leaf" << '\n';
}
