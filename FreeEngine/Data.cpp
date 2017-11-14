#include "Data.h"
#include <Windows.h>

#include "Debug.h"

std::unique_ptr<Data> Data::_instance;
std::once_flag Data::onceFlag;

Data::Data()
{
	RecoverProjetPath();
}

Data::~Data()
{
}

void Data::RecoverProjetPath()
{
	char result[MAX_PATH];
	size_t size = GetModuleFileName(NULL, (LPWSTR)result, MAX_PATH);
	std::string temp = std::string(result, size);

	for (int i = 0; i < (int)size; ++i)
	{
		if (temp[i] == '\\')
		{
			_projectPath += '/';
			continue;
		}

		if (i % 2 == 0 && temp[i])
			_projectPath += temp[i];
	}
	_projectPath += '/';
}

const std::string Data::GetProjetPath()
{
	return _projectPath;
}