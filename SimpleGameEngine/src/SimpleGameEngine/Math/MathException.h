#pragma once
#include <stdexcept>

namespace SimpleGameEngine::Math
{
	class MathException
		: public std::exception
	{
	public:
		MathException();
		MathException(const char * message);
		virtual ~MathException();
	};
}

