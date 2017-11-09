#include "TestLeaf.h"
#include "Debug.h"

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

void TestLeaf::Update(float deltaTime)
{
	//std::cout << "Update test leaf" << '\n';
}

void TestLeaf::Exit()
{
	Debug::Instance().Print("Exit test leaf", DebugMessageType::DEBUGLOG);
}

void TestLeaf::Render()
{
	//std::cout << "Render test leaf" << '\n';
}
