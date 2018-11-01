#include "IOException.h"
#include 

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
