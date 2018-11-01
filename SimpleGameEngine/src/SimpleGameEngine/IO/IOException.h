#pragma once
#include <exception>
#include <string>

namespace SimpleGameEngine::IO
{
	class IOException : public std::exception
	{
	public:
		IOException();
		IOException(std::string message);
		virtual ~IOException();
	};
}
