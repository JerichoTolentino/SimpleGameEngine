#include "FileUtils.h"
#include "IOException.h"
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
		std::ifstream ifs(filepath);
		std::string content(
			(std::istreambuf_iterator<char>(ifs)), 
			(std::istreambuf_iterator<char>()));

		return content;
	}
}
