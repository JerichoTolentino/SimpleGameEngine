#include "sgepch.h"
#include "IOException.h"

namespace SimpleGameEngine::IO
{
	IOException::IOException()
	{
	}

	IOException::IOException(std::string message)
		: std::exception(message.c_str())
	{
	}

	IOException::~IOException()
	{
	}
}
