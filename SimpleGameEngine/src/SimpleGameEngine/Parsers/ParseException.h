#pragma once
#include <string>
#include <exception>

namespace SimpleGameEngine::Parsers
{
	class ParseException : public std::exception
	{
	public:
		ParseException();
		ParseException(std::string message);
		virtual ~ParseException();
	};
}
