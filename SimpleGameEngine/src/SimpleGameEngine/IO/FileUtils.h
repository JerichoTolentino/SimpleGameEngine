#pragma once
#include <string>

namespace SimpleGameEngine::IO
{
	class FileUtils
	{
	private:
		FileUtils();
	public:
		~FileUtils();

		static std::string loadFileToString(std::string filepath);
	};
}
