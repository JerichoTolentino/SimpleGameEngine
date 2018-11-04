#include "ObjectFileLoader.h"

#include <fstream>
#include "Loader.h"
#include "../IO/FileUtils.h"
#include "../Models/BoundingBox.h"

#define TEST_INDICES 6

using namespace SimpleGameEngine::IO;
using namespace SimpleGameEngine::Math;
using namespace SimpleGameEngine::Models;

namespace SimpleGameEngine::Loaders
{
	std::string nextSubStr(std::string &line, std::string delim);

	ObjectFileLoader::ObjectFileLoader()
	{
	}


	ObjectFileLoader::~ObjectFileLoader()
	{
	}

	GeometryModel ObjectFileLoader::loadObjFile(std::string filepath, std::string texturefilepath)
	{
		std::vector<Vec3> vertices;
		std::vector<Vec2> textures;
		std::vector<Vec3> normals;
		std::vector<GLuint> indices;
		std::vector<Vec2> orderedTextures;
		std::vector<Vec3> orderedNormals;
		Material material;

		bool created = false;

		//--For BoundingBox--//

		float minx, miny, minz, maxx, maxy, maxz;
		bool firstSet = false;

		//--End For BoundingBox--//

		std::ifstream file = FileUtils::openFile(filepath);

		while (file.good())
		{
			char ln[100];
			file.getline(ln, 100);
			//std::cout << "line: " << ln << std::endl;
			std::string line(ln), delim(" ");

			std::string curr = nextSubStr(line, delim);

			if (curr == "#")
				continue;
			else if (curr == "mtllib")
			{
				//read material file
				curr = nextSubStr(line, delim);

				material = ObjectFileLoader::loadMaterial(curr, texturefilepath);
			}
			else if (curr == "v")
			{
				//add vertex
				curr = nextSubStr(line, delim);
				float x = (float) atof(curr.c_str());

				curr = nextSubStr(line, delim);
				float y = (float) atof(curr.c_str());

				curr = nextSubStr(line, delim);
				float z = (float) atof(curr.c_str());

				if (!firstSet)
				{
					minx = x;	maxx = x;
					miny = y;	maxy = y;
					minz = z;	maxz = z;
					firstSet = true;
				}
				else
				{
					if (x < minx)
						minx = x;
					if (x > maxx)
						maxx = x;
					if (y < miny)
						miny = y;
					if (y > maxy)
						maxy = y;
					if (z < minz)
						minz = z;
					if (z > maxz)
						maxz = z;
				}

				vertices.push_back(Vec3(x, y, z));

				//mostly here for future implementation of mutliple meshes in .obj file...
				if (created)
				{
					created = false;
				}
			}
			else if (curr == "vt")
			{
				//add texture coord
				curr = nextSubStr(line, delim);
				float x = (float) atof(curr.c_str());

				curr = nextSubStr(line, delim);
				float y = (float) atof(curr.c_str());

				textures.push_back(Vec2(x, y));

				//std::cout << "Texture: (" << x << "," << y << ")" << std::endl;
			}
			else if (curr == "vn")
			{
				//add normal
				curr = nextSubStr(line, delim);
				float x = (float)atof(curr.c_str());

				curr = nextSubStr(line, delim);
				float y = (float)atof(curr.c_str());

				curr = nextSubStr(line, delim);
				float z = (float)atof(curr.c_str());

				normals.push_back(Vec3(x, y, z));

				//std::cout << "Normal: (" << x << "," << y << "," << z << ")" << std::endl;
			}
			else if (curr == "f")
			{
				//create new; also for multiple mesh implementation
				if (!created)
				{
					orderedTextures.resize(vertices.size());
					orderedNormals.resize(vertices.size());

					created = true;
				}

				//process face
				//std::cout << "Face: " << line << std::endl;

				curr = nextSubStr(line, delim); //vertex 1
				processVertex(textures, normals, indices, curr, orderedTextures, orderedNormals);

				curr = nextSubStr(line, delim); //vertex 2
				processVertex(textures, normals, indices, curr, orderedTextures, orderedNormals);

				curr = nextSubStr(line, delim); //vertex 3
				processVertex(textures, normals, indices, curr, orderedTextures, orderedNormals);
			}
		}

		GeometryModel model(vertices, textures, normals, indices);
		GLuint vaoId = Loader::loadGeometryModel(model);
		GLuint textureId = Loader::loadTexture(texturefilepath);
		// TODO: do something with these IDs

		BoundingBox boundingBox = BoundingBox(minx, miny, minz, maxx, maxy, maxz);
		// TODO: do something with this

		file.close();

		return model;
	}

	void ObjectFileLoader::processVertex(std::vector<Vec2> textures, std::vector<Vec3> normals, std::vector<GLuint> indices, std::string vertexStr, std::vector<Vec2> texts, std::vector<Vec3> norms)
	{
		GLuint vIndex, tIndex, nIndex;

		// Parse face
		vIndex = atoi(nextSubStr(vertexStr, "/").c_str()) - 1;
		tIndex = atoi(nextSubStr(vertexStr, "/").c_str()) - 1;
		nIndex = atoi(nextSubStr(vertexStr, "/").c_str()) - 1;

		indices.push_back(vIndex);

		// Align texture and normals with vertices vector
		Vec2 texture = textures.at(tIndex);
		Vec3 normal = normals.at(nIndex);

		texts[vIndex * 2] = texture; //NOTE: May have to 1 - texture.y for this...
		norms[vIndex * 3] = normal;
	}

	Material ObjectFileLoader::loadMaterial(std::string filepath, std::string texturepath)
	{
		std::string path = "res/models/";
		path.append(filepath);

		std::ifstream materialFile = FileUtils::openFile(filepath);

		float a, e, d, s, sh, ri, r, t;
		r = 0.0f;
		std::string name = "";
		GLuint textureID = Loader::loadTexture(texturepath);

		while (materialFile.good())
		{
			char ln[100];
			materialFile.getline(ln, 100);
			std::string line(ln), delim(" ");

			std::string curr = nextSubStr(line, delim);

			//NOTE: mtl files in rgb but this engine only cares about 1 value for all rgb; takes average

			if (curr == "#")
				continue;
			else if (curr == "newmtl")
			{
				name = nextSubStr(line, delim);
			}
			else if (curr == "Ns")
			{
				curr = nextSubStr(line, delim);
				sh = (float) atof(curr.c_str());
			}
			else if (curr == "Ka")
			{
				curr = nextSubStr(line, delim);
				a = (float) atof(curr.c_str());
				curr = nextSubStr(line, delim);
				a += (float) atof(curr.c_str());
				curr = nextSubStr(line, delim);
				a += (float) atof(curr.c_str());

				a /= 3;
			}
			else if (curr == "Kd")
			{
				curr = nextSubStr(line, delim);
				d = (float) atof(curr.c_str());
				curr = nextSubStr(line, delim);
				d += (float) atof(curr.c_str());
				curr = nextSubStr(line, delim);
				d += (float) atof(curr.c_str());

				d /= 3;
			}
			else if (curr == "Ks")
			{
				curr = nextSubStr(line, delim);
				s = (float) atof(curr.c_str());
				curr = nextSubStr(line, delim);
				s += (float) atof(curr.c_str());
				curr = nextSubStr(line, delim);
				s += (float) atof(curr.c_str());

				s /= 3;
			}
			else if (curr == "Ke")
			{
				curr = nextSubStr(line, delim);
				e = (float) atof(curr.c_str());
				curr = nextSubStr(line, delim);
				e += (float) atof(curr.c_str());
				curr = nextSubStr(line, delim);
				e += (float) atof(curr.c_str());

				e /= 3;
			}
			else if (curr == "Ni")
			{
				curr = nextSubStr(line, delim);
				ri = (float) atof(curr.c_str());
			}
			else if (curr == "d")
			{
				curr = nextSubStr(line, delim);
				t = (float) atof(curr.c_str());
			}

		}

		materialFile.close();

		LightingModel lightingModel = LightingModel(0.0f, t, a, e, d, s, sh, ri);

		return Material(lightingModel);
	}

	//find & return the next substring in 'line'. removes that substring from beginning of 'line'.
	std::string nextSubStr(std::string &line, std::string delim)
	{
		std::string substring;
		size_t pos = line.find(delim);

		if (pos != std::string::npos)
		{
			substring = line.substr(0, pos);
			line.erase(0, pos + delim.length());
		}
		else
		{
			substring = line;
			line.clear();
		}

		return substring;
	}
}
