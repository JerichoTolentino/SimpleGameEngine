#pragma once
#include <exception>
#include <string>

namespace SimpleGameEngine::Math
{
	class MathException
		: public std::exception
	{
	public:
		MathException();
		MathException(std::string message);
		virtual ~MathException();
	};
}

