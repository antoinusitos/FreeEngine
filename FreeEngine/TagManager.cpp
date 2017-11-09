#include "TagManager.h"
#include "Debug.h"

std::unique_ptr<TagManager> TagManager::_instance;
std::once_flag TagManager::onceFlag;

TagManager::TagManager()
{
}

TagManager::~TagManager()
{
}

void TagManager::AddTag(std::string newTag)
{
	for (auto& pairTag : _tags)
	{
		if (pairTag.second == newTag)
		{
			Debug::Instance().Print("TagManager already has tag " + newTag, DebugMessageType::DEBUGENGINE);
			return;
		}
	}
	
	_tags.emplace((int)_tags.size(), newTag);
}

void TagManager::RemoveTag(std::string newTag)
{
	bool found = false;
	int index = 0;
	for (auto& pairTag : _tags)
	{
		if (pairTag.second == newTag)
		{
			index = pairTag.first;
			found = true;
			break;
		}
	}

	if (found)
	{
		_tags.erase(index);
	}
	else
	{
		Debug::Instance().Print("TagManager does not have tag " + newTag, DebugMessageType::DEBUGENGINE);
	}
}

int TagManager::GetTagID(std::string tag)
{
	for (auto& pairTag : _tags)
	{
		if (pairTag.second == tag)
		{
			return pairTag.first;
		}
	}
	return -1;
}