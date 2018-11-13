#include "MaterialLibraryParser.h"
#include <fstream>
#include "../IO/FileUtils.h"
#include "../Utility/StringUtil.h"
#include "ParseException.h"
#include "../Log.h"

using namespace SimpleGameEngine::Models;
using namespace SimpleGameEngine::IO;
using namespace SimpleGameEngine::Utility;

namespace SimpleGameEngine::Parsers
{
	const std::string MaterialLibraryParser::AMBIENT_LINE = "Ka";
	const std::string MaterialLibraryParser::DIFFUSE_LINE = "Kd";
	const std::string MaterialLibraryParser::SPECULAR_LINE = "Ks";
	const std::string MaterialLibraryParser::EMISSIVE_LINE = "Ke";
	const std::string MaterialLibraryParser::SPECULAR_EXP_LINE = "Ns";
	const std::string MaterialLibraryParser::OPACITY_LINE = "d";
	const std::string MaterialLibraryParser::REFRACTIVE_INDEX_LINE = "Ni";



	Models::Material MaterialLibraryParser::parseFile(const std::string & filepath)
	{
		float emissive;
		float ambient;
		float diffuse;
		float specular;
		float specularHighlight;
		float opacity;
		float refractiveIndex;

		std::string line;
		std::ifstream file = FileUtils::openFile(filepath);
		while (std::getline(file, line))
		{
			// NOTE: mtl files are in rgb but this engine only cares about 1 value for all rgb; takes average
			auto tokens = StringUtil::split(line);

			if (tokens.at(0) == SPECULAR_EXP_LINE)
			{
				if (tokens.size() != 2)
					throw ParseException("Exactly 1 value is required for the specular exponent.");

				specularHighlight = (float) atof(tokens.at(1).c_str());
			}
			else if (tokens.at(0) == AMBIENT_LINE)
			{
				if (tokens.size() != 4)
					throw ParseException("Exactly 3 values are required for the ambient constant.");

				float r = (float) atof(tokens.at(1).c_str());
				float g = (float) atof(tokens.at(2).c_str());
				float b = (float) atof(tokens.at(3).c_str());

				ambient = (r + g + b) / 3;
			}
			else if (tokens.at(0) == DIFFUSE_LINE)
			{
				if (tokens.size() != 4)
					throw ParseException("Exactly 3 values are required for the diffuse constant.");

				float r = (float) atof(tokens.at(1).c_str());
				float g = (float) atof(tokens.at(2).c_str());
				float b = (float) atof(tokens.at(3).c_str());

				diffuse = (r + g + b) / 3;
			}
			else if (tokens.at(0) == SPECULAR_LINE)
			{
				if (tokens.size() != 4)
					throw ParseException("Exactly 3 values are required for the specular constant.");

				float r = (float) atof(tokens.at(1).c_str());
				float g = (float) atof(tokens.at(2).c_str());
				float b = (float) atof(tokens.at(3).c_str());

				specular = (r + g + b) / 3;
			}
			else if (tokens.at(0) == EMISSIVE_LINE)
			{
				if (tokens.size() != 4)
					throw ParseException("Exactly 3 values are required for the emissive constant.");

				float r = (float) atof(tokens.at(1).c_str());
				float g = (float) atof(tokens.at(2).c_str());
				float b = (float) atof(tokens.at(3).c_str());

				emissive = (r + g + b) / 3;
			}
			else if (tokens.at(0) == REFRACTIVE_INDEX_LINE)
			{
				if (tokens.size() != 2)
					throw ParseException("Exactly 1 value is required for the refractive index.");

				refractiveIndex = (float) atof(tokens.at(1).c_str());
			}
			else if (tokens.at(0) == OPACITY_LINE)
			{
				if (tokens.size() != 2)
					throw ParseException("Exactly 1 value is required for the opacity value.");

				opacity = (float) atof(tokens.at(1).c_str());
			}
		}

		file.close();

		SGE_CORE_TRACE("Parsed material file {0} with opacity {1}, ambient {2}, emissive {3}, diffuse {4}, specular {5}, specular highlight {6}, refractive index {7}",
			filepath, opacity, ambient, emissive, diffuse, specular, specularHighlight, refractiveIndex);

		auto lightingModel = std::make_shared<LightingModel>(LightingModel(0.0f, opacity, ambient, emissive, diffuse, specular, specularHighlight, refractiveIndex));
		return Material(lightingModel);
	}
}
