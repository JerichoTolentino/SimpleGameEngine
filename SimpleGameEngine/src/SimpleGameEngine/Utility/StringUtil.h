#pragma once
#include <string>
#include <vector>

namespace SimpleGameEngine::Utility
{
	class StringUtil
	{
	public:
		static std::vector<std::string> split(std::string string, const std::string & delimiter = " ");
	};
}
