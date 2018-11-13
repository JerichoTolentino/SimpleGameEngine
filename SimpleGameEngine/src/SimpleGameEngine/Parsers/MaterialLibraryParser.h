#pragma once
#include <string>
#include "../Models/Material.h"

namespace SimpleGameEngine::Parsers
{
	class MaterialLibraryParser
	{
	public:
		static const std::string AMBIENT_LINE;
		static const std::string DIFFUSE_LINE;
		static const std::string SPECULAR_LINE;
		static const std::string EMISSIVE_LINE;
		static const std::string SPECULAR_EXP_LINE;
		static const std::string OPACITY_LINE;
		static const std::string REFRACTIVE_INDEX_LINE;



		/// <summary>
		/// Parses a material library file into a <see cref="Material"/>.
		/// </summary>
		/// <param name="filepath"></param>
		/// <returns></returns>
		/// <exception cref="ParseException"></exception>
		static Models::Material parseFile(const std::string & filepath);
	};
}
