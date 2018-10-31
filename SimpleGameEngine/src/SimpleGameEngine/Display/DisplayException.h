#pragma once
#include <exception>

namespace SimpleGameEngine::Display
{
	class DisplayException :
		public std::exception
	{
	public:
		DisplayException();
		DisplayException(const char* message);
		~DisplayException();
	};
}
