#pragma once
#include <exception>
#include <string>

namespace SimpleGameEngine::Loaders
{
	class TextureLoadException : public std::exception
	{
	public:
		TextureLoadException();
		TextureLoadException(std::string message);
		virtual ~TextureLoadException();
	};
}
