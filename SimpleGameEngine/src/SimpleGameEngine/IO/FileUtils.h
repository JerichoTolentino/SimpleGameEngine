#pragma once
#include <string>

namespace SimpleGameEngine::IO
{
	class FileUtils
	{
		/// <summary>
		/// Reads the entire contents of a file into a <see cref="std::string"/>.
		/// </summary>
		/// <param name="filepath">The path to the file to read.</param>
		/// <returns></returns>
		/// <exception cref="IOException"></exception>
		static std::string loadFileToString(std::string filepath);

		/// <summary>
		/// Opens a file.
		/// </summary>
		/// <param name="filepath"></param>
		/// <returns></returns>
		/// <exception cref="IOException"></exception>
		static std::ifstream openFile(std::string filepath);
	};
}
