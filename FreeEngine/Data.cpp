#include "Data.h"
#include <Windows.h>

#include "Debug.h"

std::unique_ptr<Data> Data::_instance;
std::once_flag Data::onceFlag;

Data::Data()
{
	GetProjetPath();
}

Data::~Data()
{
}

void Data::GetProjetPath()
{
	char result[MAX_PATH];
	size_t size = GetModuleFileName(NULL, (LPWSTR)result, MAX_PATH);
	std::string temp = std::string(result, size);

	for (int i = 0; i < size; ++i)
	{
		if (temp[i] == '\\')
		{
			projectPath += '/';
			continue;
		}

		if (i % 2 == 0 && temp[i])
			projectPath += temp[i];
	}
	projectPath += '/';

	Debug::Instance().Print("project path:" + projectPath + '\n');
}