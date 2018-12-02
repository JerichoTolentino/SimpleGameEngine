#include "sgepch.h"
#include "ParseException.h"

namespace SimpleGameEngine::Parsers
{
	ParseException::ParseException()
	{
	}

	ParseException::ParseException(std::string message)
		: std::exception(message.c_str())
	{
	}

	ParseException::~ParseException()
	{
	}
}
