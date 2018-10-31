#include "MathException.h"

namespace SimpleGameEngine::Math
{
	MathException::MathException()
		: std::exception("An unexpected math error occurred.")
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
