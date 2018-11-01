#pragma once
#include <exception>
#include <string>

namespace SimpleGameEngine::Display
{
	class DisplayException : public std::exception
	{
	public:
		DisplayException();
		DisplayException(std::string message);
		virtual ~DisplayException();
	};
}
