#include "sgepch.h"
#include "MathException.h"

namespace SimpleGameEngine::Math
{
	MathException::MathException()
		: std::exception("An unexpected math error occurred.")
	{
	}

	MathException::MathException(std::string message)
		: std::exception(message.c_str())
	{
	}

	MathException::~MathException()
	{
	}
}
