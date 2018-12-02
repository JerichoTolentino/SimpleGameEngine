#include "sgepch.h"
#include "DisplayException.h"

namespace SimpleGameEngine::Display
{
	DisplayException::DisplayException()
		: std::exception("An unexpected display exception occurred.")
	{
	}

	DisplayException::DisplayException(std::string message)
		: std::exception(message.c_str())
	{
	}


	DisplayException::~DisplayException()
	{
	}
}
