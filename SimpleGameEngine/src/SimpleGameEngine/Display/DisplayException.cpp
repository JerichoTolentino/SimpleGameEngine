#include "DisplayException.h"

namespace SimpleGameEngine::Display
{
	DisplayException::DisplayException()
		: std::exception("An unexpected display exception occurred.")
	{
	}

	DisplayException::DisplayException(const char * message)
		: std::exception(message)
	{
	}


	DisplayException::~DisplayException()
	{
	}
}
