#include "sgepch.h"
#include "StringUtil.h"

namespace SimpleGameEngine::Utility
{
	std::vector<std::string> StringUtil::split(std::string string, const std::string & delimiter)
	{
		std::vector<std::string> split;

		int stride = (int) delimiter.length();
		int start = 0;
		int next = (int) string.find(delimiter, 0);

		// Special case
		if (next == std::string::npos)
		{
			split.push_back(string);
			return split;
		}

		// Loop until string is split
		do
		{
			// Add token
			split.push_back(string.substr(start, next - start));

			// Calculate start of next token
			start = next + stride;
			if (start >= string.length())
				break;

			// Calculate end of next token
			next = (int) string.find(delimiter, start);
		} while (next != std::string::npos);

		// Add last element
		if (start < string.length())
			split.push_back(string.substr(start, string.length() - start));

		return split;
	}
}
