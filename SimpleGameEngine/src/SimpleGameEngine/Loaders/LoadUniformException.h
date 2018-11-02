#pragma once
#include <exception>
#include <string>

namespace SimpleGameEngine::Loaders
{
	class LoadUniformException : std::exception
	{
	public:
		LoadUniformException();
		LoadUniformException(std::string message);
		virtual ~LoadUniformException();
	};
}
