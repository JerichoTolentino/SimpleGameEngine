#pragma once
#include <string>

namespace SimpleGameEngine::IO
{
	class FileUtils
	{
	private:
		FileUtils();
	public:
		~FileUtils();

		/// <summary>
		/// Reads the entire contents of a file into a <see cref="std::string"/>.
		/// </summary>
		/// <param name="filepath">The path to the file to read.</param>
		/// <returns></returns>
		static std::string loadFileToString(std::string filepath);
	};
}
