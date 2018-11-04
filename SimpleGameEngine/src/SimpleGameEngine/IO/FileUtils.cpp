#include "FileUtils.h"
#include "IOException.h"
#include <fstream>

namespace SimpleGameEngine::IO
{
	std::string FileUtils::loadFileToString(std::string filepath)
	{
		std::ifstream ifs = openFile(filepath);
		std::string content(
			(std::istreambuf_iterator<char>(ifs)), 
			(std::istreambuf_iterator<char>()));

		return content;
	}

	std::ifstream FileUtils::openFile(std::string filepath)
	{
		std::ifstream ifs;
		
		ifs.open(filepath.c_str());
		if (!ifs.is_open())
			throw IOException("Failed to open file " + filepath);

		return ifs;
	}

}
