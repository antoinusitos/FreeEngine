#include "FileHandler.h"

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

#include "Data.h"

std::unique_ptr<FileHandler> FileHandler::_instance;
std::once_flag FileHandler::onceFlag;

FileHandler::FileHandler()
{
	ids = 0;
}

FileHandler::~FileHandler()
{
	_allWatcher.empty();
}

bool FileHandler::WriteFile(std::string fileName, std::string text)
{
	std::ofstream myfile(fileName);
	if (myfile.is_open())
	{
		myfile << text;
		myfile.close();
		return true;
	}
	return false;
}

std::string FileHandler::ReadFile(std::string fileName, bool* fileReadable)
{
	std::string returnString = "";

	std::ifstream myfile(fileName);
	if (myfile.is_open())
	{
		*fileReadable = true;
		std::string line;
		while (std::getline(myfile, line))
		{
			returnString += line + '\n';
		}
		myfile.close();
	}
	else
	{
		*fileReadable = false;
	}

	return returnString;
}

int FileHandler::RegisterNewWatcher(FileObserver* observer, std::string fileName)
{
	Watcher newWatcher = Watcher();
	newWatcher.ID = ids;
	newWatcher.observer = observer;
	newWatcher.fileToObserve = Data::Instance().GetProjetPath() + fileName;
	ids++;
	_allWatcher.push_back(newWatcher);

	return ids;
}

void FileHandler::UpdateWatchers(float deltaTime)
{
	for (std::vector<Watcher>::iterator it = _allWatcher.begin(); it != _allWatcher.end(); ++it)
	{		
		struct stat buf;
		int result;
		struct tm timeinfo;
		char buffer[80];
		char const *filename = (it)->fileToObserve.c_str();

		// Get data associated with "crt_stat.c":
		result = stat(filename, &buf);

		// Check if statistics are valid:
		if (result != 0)
		{
			perror("Problem getting information");
			switch (errno)
			{
			case ENOENT:
				printf("File %s not found.\n", filename);
				break;
			case EINVAL:
				printf("Invalid parameter to _stat.\n");
				break;
			default:
				// Should never be reached.
				printf("Unexpected error in _stat.\n");
			}
		}
		else
		{
			localtime_s(&timeinfo, &buf.st_mtime);
			strftime(buffer, sizeof(buffer), "%d-%m-%Y_%I-%M-%S", &timeinfo);


			// different date !
			if ((it)->lastTime != buf.st_mtime)
			{
				(it)->observer->NotifyChange();
			}

			(it)->lastTime = buf.st_mtime;
		}

	}
}

void FileHandler::UnregisterWatcher(int ID)
{
	int index = -1;
	bool found = false;
	for (std::vector<Watcher>::iterator it = _allWatcher.begin(); it != _allWatcher.end(); ++it)
	{
		index++;
		if ((it)->ID == ID)
		{
			found = true;
			break;
		}
	}
	if (found)
	{
		_allWatcher.erase(_allWatcher.begin() + index);
	}
}