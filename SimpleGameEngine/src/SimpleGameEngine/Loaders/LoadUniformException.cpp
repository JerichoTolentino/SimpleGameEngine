#include "sgepch.h"
#include "LoadUniformException.h"

namespace SimpleGameEngine::Loaders
{
	LoadUniformException::LoadUniformException()
	{
	}

	LoadUniformException::LoadUniformException(std::string message)
		: std::exception(message.c_str())
	{
	}


	LoadUniformException::~LoadUniformException()
	{
	}
}
