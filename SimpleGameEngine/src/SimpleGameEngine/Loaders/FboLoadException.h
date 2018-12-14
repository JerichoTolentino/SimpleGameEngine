#pragma once

namespace SimpleGameEngine::Loaders
{
	class FboLoadException : public std::exception
	{
	public:
		FboLoadException();
		FboLoadException(const std::string & message);
		virtual ~FboLoadException();
	};
}
