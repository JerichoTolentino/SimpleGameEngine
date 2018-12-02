#include "sgepch.h"
#include "WavefrontObjParser.h"

#include "../IO/FileUtils.h"
#include "../Utility/StringUtil.h"
#include "ParseException.h"

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



	Models::GeometryModel WavefrontObjParser::parseFile(const std::string & filepath)
	{
		// Source sets of elements
		auto vertices = std::make_shared<std::vector<Vec3>>();
		std::vector<Vec2> textureUvs;
		std::vector<Vec3> normals;

		// Final aligned collections of elements
		// Note: They are aligned to the vertices collection - that one doesn't need to change
		auto alignedTextureUvs = std::make_shared<std::vector<Vec2>>();
		auto alignedNormals = std::make_shared<std::vector<Vec3>>();

		// Vertex indices to render with an index array
		auto indices = std::make_shared<std::vector<unsigned int>>();

		// Handles texture seams
		// Vector of flags indicating if a vertex at some position has been processed
		// Vector of Vector<WavefrontObjVertex> storing all duplicate vertices
		std::vector<bool> processedVertices;
		std::vector<std::vector<WavefrontObjVertex>> processedVertexData;

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
				vertices->push_back(Vec3(x, y, z));
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
					int size = vertices->size();

					// Resize aligned vectors to match the number of vertices
					alignedTextureUvs->resize(size);
					alignedNormals->resize(size);

					// Resize texture seam handling stuff
					processedVertices.resize(size);
					processedVertexData.resize(size);

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

					if (!processedVertices.at(vertexIndex))
					{
						// Align elements with vertices
						alignedTextureUvs->at(vertexIndex) = textureUvs.at(uvIndex);
						alignedNormals->at(vertexIndex) = normals.at(normalIndex);

						// Build index array
						indices->push_back(vertexIndex);

						// Add processed vertex
						processedVertices.at(vertexIndex) = true;
						processedVertexData.at(vertexIndex).push_back(WavefrontObjVertex(vertexIndex, uvIndex, normalIndex));
					}
					else
					{
						// Handle multiple texture/normal coordinates associated with a single vertex
						// Look for an equivalent vertex data
						auto vertexDataList = processedVertexData.at(vertexIndex);
						WavefrontObjVertex current(vertexIndex, uvIndex, normalIndex);
						auto vertexDataIter = std::find(vertexDataList.begin(), vertexDataList.end(), current);

						if (vertexDataIter != vertexDataList.end())
						{
							// Found an actual duplicate - just add the index as usual
							indices->push_back(vertexIndex);
						}
						else
						{
							// Need to create a duplicate position vertex for the uv/normal pair

							// Duplicate position vertex
							Vec3 position = vertices->at(vertexIndex);
							vertices->push_back(Vec3(position));
							int duplicateVertexIndex = vertices->size() - 1;

							// Add duplicate texture and normal values
							alignedTextureUvs->push_back(textureUvs.at(uvIndex));
							alignedNormals->push_back(normals.at(normalIndex));

							// Create new vertex data with new position, uv, and normal indexes
							WavefrontObjVertex duplicateVertexData(duplicateVertexIndex, uvIndex, normalIndex);
							vertexDataList.push_back(duplicateVertexData);
							
							// Push back new vertex index
							indices->push_back(duplicateVertexIndex);
						}
					}
				}
			}
			else if (tokens.at(0) == PARAM_SPACE_VERTEX_LINE || tokens.at(0) == LINE_ELEMENT_LINE)
				throw ParseException("Parameter space vertices and line elements in wavefront OBJ files are currently not supported.");
		}

		SGE_CORE_TRACE("Parsed wavefront obj file {0} with {1} vertices, {2} texture uvs, {3} normals, and {4} indices",
			filepath, vertices->size(), alignedTextureUvs->size(), alignedNormals->size(), indices->size());

		return Models::GeometryModel(vertices, alignedTextureUvs, alignedNormals, indices);
	}


	
#pragma region WavefrontObjVertex

	WavefrontObjParser::WavefrontObjVertex::WavefrontObjVertex()
	{
	}

	WavefrontObjParser::WavefrontObjVertex::WavefrontObjVertex(int positionIndex, int textureUvIndex, int normalIndex)
	{
		m_positionIndex = positionIndex;
		m_textureUvIndex = textureUvIndex;
		m_normalIndex = normalIndex;
	}
	
	WavefrontObjParser::WavefrontObjVertex::WavefrontObjVertex(const WavefrontObjVertex & other)
		: WavefrontObjVertex(other.m_positionIndex, other.m_textureUvIndex, other.m_normalIndex)
	{
	}
	
	WavefrontObjParser::WavefrontObjVertex::~WavefrontObjVertex()
	{
	}
	
	
	
	int WavefrontObjParser::WavefrontObjVertex::getPositionIndex() const
	{
		return m_positionIndex;
	}
	
	int WavefrontObjParser::WavefrontObjVertex::getTextureUvIndex() const
	{
		return m_textureUvIndex;
	}
	
	int WavefrontObjParser::WavefrontObjVertex::getNormalIndex() const
	{
		return m_normalIndex;
	}
	
	
	
	WavefrontObjParser::WavefrontObjVertex & WavefrontObjParser::WavefrontObjVertex::operator=(const WavefrontObjVertex & other)
	{
		m_positionIndex = other.m_positionIndex;
		m_textureUvIndex = other.m_textureUvIndex;
		m_normalIndex = other.m_normalIndex;

		return *this;
	}

	bool WavefrontObjParser::WavefrontObjVertex::operator==(const WavefrontObjVertex & other)
	{
		return
			m_positionIndex == other.m_positionIndex &&
			m_textureUvIndex == other.m_textureUvIndex &&
			m_normalIndex == other.m_normalIndex;
	}

#pragma endregion

}
