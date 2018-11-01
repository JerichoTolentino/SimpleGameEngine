#include "FileUtils.h"
#include <fstream>

namespace SimpleGameEngine::IO
{
	FileUtils::FileUtils()
	{
	}


	FileUtils::~FileUtils()
	{
	}

	std::string SimpleGameEngine::IO::FileUtils::loadFileToString(std::string filepath)
	{
		std::string converted;
		char c;
		std::ifstream file;
		file.open(filepath);

		if (!file.is_open())
			MessageHandler::printMessage("ERROR: Cannot open " + std::string(filepath) + "!\n");

		file.get(c);

		while (!file.eof())
		{
			converted += c;
			//std::cout << c;
			file.get(c);
		}

		return converted;
	}
}
