#include "sgepch.h"
#include "FboLoadException.h"

namespace SimpleGameEngine::Loaders
{
	FboLoadException::FboLoadException()
		: std::exception()
	{
	}

	FboLoadException::FboLoadException(const std::string & message)
		: std::exception(message.c_str())
	{
	}

	FboLoadException::~FboLoadException()
	{
	}
}
