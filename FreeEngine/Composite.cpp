#include "Composite.h"

Composite::Composite()
{
}

Composite::~Composite()
{
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		delete (*it);
	}
	components.clear();
}

void Composite::AddComponent(Component* newLeaf)
{
	newLeaf->_parent = this;
	components.push_back(newLeaf);
}

void Composite::RemoveComponent(Component* leafToRemove)
{
	int index = -1;
	bool found = false;
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		index++;
		if ((*it) == leafToRemove)
		{
			found = true;
			break;
		}
	}

	if (found)
		components.erase(components.begin() + index);
}

void Composite::Awake()
{
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Awake();
	}
}

void Composite::Start()
{
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Start();
	}
}

void Composite::Update(const float deltaTime)
{
	for (std::vector<Composite*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		(*it)->transform.position = transform.position + (*it)->transformFromParent.position;
		(*it)->transform.rotation = transform.rotation + (*it)->transformFromParent.rotation;
		(*it)->transform.scale = transform.scale * (*it)->transformFromParent.scale;
	}

	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Update(deltaTime);
	}
}

void Composite::Render(sf::RenderWindow* window)
{
	for (std::vector<Composite*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		(*it)->Render(window);
	}

	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Render(window);
	}
}

void Composite::Exit()
{
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Exit();
	}
}

void Composite::AddChild(Composite* newChild)
{
	children.push_back(newChild);
	newChild->_parent = this;
	newChild->transformFromParent.position = newChild->transform.position - transform.position;
	newChild->transformFromParent.rotation = newChild->transform.rotation - transform.rotation;
	newChild->transformFromParent.scale = newChild->transform.scale / transform.scale;

}

void Composite::RemoveChild(Composite* child)
{
	int index = -1;
	bool found = false;
	for (std::vector<Composite*>::iterator it = children.begin(); it != children.end(); ++it)
	{
		index++;
		if ((*it) == child)
		{
			found = true;
			break;
		}
	}

	if (found)
	{
		children[index]->_parent = nullptr;
		children.erase(children.begin() + index);
	}
}