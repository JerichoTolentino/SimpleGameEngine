#include "MathException.h"

namespace SimpleGameEngine::Math
{
	MathException::MathException()
		: std::exception("An unknown math error occurred.")
	{
	}

	MathException::MathException(const char * message)
		: std::exception(message)
	{
	}

	MathException::~MathException()
	{
	}
}
