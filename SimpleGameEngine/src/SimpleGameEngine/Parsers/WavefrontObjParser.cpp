#include "WavefrontObjParser.h"
#include <fstream>
#include <vector>
#include "../IO/FileUtils.h"
#include "../Utility/StringUtil.h"
#include "ParseException.h"
#include "../Log.h"

using namespace SimpleGameEngine::IO;
using namespace SimpleGameEngine::Utility;
using namespace SimpleGameEngine::Math;

namespace SimpleGameEngine::Parsers
{
	const std::string WavefrontObjParser::VERTEX_LINE = "v";
	const std::string WavefrontObjParser::TEXTURE_UV_LINE = "vt";
	const std::string WavefrontObjParser::NORMAL_LINE = "vn";
	const std::string WavefrontObjParser::PARAM_SPACE_VERTEX_LINE = "vp";
	const std::string WavefrontObjParser::FACE_LINE = "f";
	const std::string WavefrontObjParser::LINE_ELEMENT_LINE = "l";



	Models::GeometryModel WavefrontObjParser::parseFile(std::string filepath)
	{
		// Source sets of elements
		std::vector<Vec3> vertices;
		std::vector<Vec2> textureUvs;
		std::vector<Vec3> normals;

		// Final aligned collections of elements
		// Note: They are aligned to the vertices collection - that one doesn't need to change
		std::vector<Vec2> alignedTextureUvs;
		std::vector<Vec3> alignedNormals;

		// Vertex indices to render with an index array
		std::vector<unsigned int> indices;

		bool finalArraysInitialized = false;

		std::string line;
		std::ifstream file = FileUtils::openFile(filepath);
		while (std::getline(file, line))
		{
			auto tokens = StringUtil::split(line);
			if (tokens.at(0) == VERTEX_LINE)
			{
				// Parse vertex line
				if (tokens.size() < 4)
					throw ParseException("Missing data in vertex line of wavefront OBJ file " + filepath);

				// Add vertex
				float x = (float) atof(tokens.at(1).c_str());
				float y = (float) atof(tokens.at(2).c_str());
				float z = (float) atof(tokens.at(3).c_str());
				vertices.push_back(Vec3(x, y, z));
			}
			else if (tokens.at(0) == TEXTURE_UV_LINE)
			{
				// Parse texture uv line
				if (tokens.size() < 3)
					throw ParseException("Missing data in texture UV line of wavefront OBJ file " + filepath);

				// Add texture UV
				float x = (float) atof(tokens.at(1).c_str());
				float y = (float) atof(tokens.at(2).c_str());
				textureUvs.push_back(Vec2(x, y));
			}
			else if (tokens.at(0) == NORMAL_LINE)
			{
				// Parse normal line
				if (tokens.size() < 4)
					throw ParseException("Missing data in normal line of wavefront OBJ file " + filepath);

				// Add vertex
				float x = (float) atof(tokens.at(1).c_str());
				float y = (float) atof(tokens.at(2).c_str());
				float z = (float) atof(tokens.at(3).c_str());
				normals.push_back(Vec3(x, y, z));
			}
			else if (tokens.at(0) == FACE_LINE)
			{
				// At this point, all vertices, texture uvs, and normals have been processed.
				// So, we have a fixed number of each of the above. We can start ordering the
				// elements to line up with the associated vertex.
				if (!finalArraysInitialized)
				{
					// Resize aligned vectors to match the number of vertices
					alignedTextureUvs.resize(vertices.size());
					alignedNormals.resize(vertices.size());

					finalArraysInitialized = true;
				}

				// Ensure faces are triangulated
				if (tokens.size() != 4)
					throw ParseException("Exactly 3 vertices per face required. Only wavefront OBJ files with triangulated faces are supported.");

				// Parse face lines
				for (int i = 1; i < tokens.size(); i++)
				{
					std::string faceToken = tokens.at(i);
					auto faceElements = StringUtil::split(faceToken, "/");

					// Validate face element
					if (faceElements.size() != 3)
						throw ParseException("Malformed face element detected: '" + faceToken + "'");

					// Parse face element (.obj files store them as 1-indexed)
					int vertexIndex = atoi(faceElements.at(0).c_str()) - 1;
					int uvIndex = atoi(faceElements.at(1).c_str()) - 1;
					int normalIndex = atoi(faceElements.at(2).c_str()) - 1;

					// Align elements with vertices
					alignedTextureUvs.at(vertexIndex) = textureUvs.at(uvIndex);
					alignedNormals.at(vertexIndex) = normals.at(normalIndex);

					// Build index array
					indices.push_back(vertexIndex);
				}
			}
			else if (tokens.at(0) == PARAM_SPACE_VERTEX_LINE || tokens.at(0) == LINE_ELEMENT_LINE)
				throw ParseException("Parameter space vertices and line elements in wavefront OBJ files are currently not supported.");
		}

		SGE_CORE_TRACE("Parsed wavefront obj file {0} with {1} vertices, {2} texture uvs, {3} normals, and {4} indices",
			filepath, vertices.size(), alignedTextureUvs.size(), alignedNormals.size(), indices.size());

		return Models::GeometryModel(vertices, alignedTextureUvs, alignedNormals, indices);
	}
}
