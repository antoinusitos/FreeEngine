#include "TestLeaf.h"

TestLeaf::TestLeaf()
{
}

TestLeaf::~TestLeaf()
{
}

void TestLeaf::Awake()
{
	std::cout << "Awake test leaf" << '\n';
}

void TestLeaf::Start()
{
	std::cout << "Start test leaf" << '\n';
}

void TestLeaf::Update(float deltaTime)
{
	//std::cout << "Update test leaf" << '\n';
}

void TestLeaf::Exit()
{
	std::cout << "Exit test leaf" << '\n';
}

void TestLeaf::Render()
{
	//std::cout << "Render test leaf" << '\n';
}
