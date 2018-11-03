#include "ObjectFileLoader.h"
#include "../IO/FileUtils.h"

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

	Model* ObjectFileLoader::loadOBJ(std::string filepath, std::string texturefilepath)
	{
		std::vector<Vec3> *vertices = new std::vector<Vec3>;
		std::vector<Vec2> *textures = new std::vector<Vec2>;
		std::vector<Vec3> *normals = new std::vector<Vec3>;
		std::vector<GLuint> *indices = new std::vector<GLuint>;

		GLfloat *verts = new GLfloat[1];
		GLfloat *texts = new GLfloat[1];
		GLfloat *norms = new GLfloat[1];
		GLuint *inds;
		Material* material = new Material();

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

				if (material != nullptr)
					delete material;

				material = ObjectFileLoader::loadMaterial(curr, texturefilepath);
			}
			else if (curr == "v")
			{
				//add vertex
				curr = nextSubStr(line, delim);
				float x = atof(curr.c_str());

				curr = nextSubStr(line, delim);
				float y = atof(curr.c_str());

				curr = nextSubStr(line, delim);
				float z = atof(curr.c_str());

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

				vertices->push_back(Vec3(x, y, z));

				//mostly here for future implementation of mutliple meshes in .obj file...
				if (created)
				{
					created = false;
					delete[]verts;
					delete[]texts;
					delete[]norms;
				}
				//std::cout << "Vertex: (" << x << "," << y << "," << z << ")" << std::endl;
			}
			else if (curr == "vt")
			{
				//add texture coord
				curr = nextSubStr(line, delim);
				float x = atof(curr.c_str());

				curr = nextSubStr(line, delim);
				float y = atof(curr.c_str());

				textures->push_back(Vec2(x, y));

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

				normals->push_back(Vec3(x, y, z));

				//std::cout << "Normal: (" << x << "," << y << "," << z << ")" << std::endl;
			}
			else if (curr == "f")
			{
				//create new; also for multiple mesh implementation
				if (!created)
				{
					//NOTE: These MUST use vertices.size()! NOT the corresponding vectors (they must 
					//all line up to the VERTEX array, so they need enough size to fit that many elements).
					//in other words, need room for duplicates!
					verts = new GLfloat[vertices->size() * 3];
					texts = new GLfloat[vertices->size() * 2];
					norms = new GLfloat[vertices->size() * 3];

					//copy vertices into verts
					for (unsigned int i = 0; i < vertices->size(); i++)
					{
						Vec3 *vertex = &(vertices->at(i));
						verts[i * 3] = vertex->x;
						verts[i * 3 + 1] = vertex->y;
						verts[i * 3 + 2] = vertex->z;
					}

					//std::cout << "Array sizes: verts[" << vertices->size() * 3 << "], texts[" << vertices->size() * 2 << "], norms[" << vertices->size() * 3 << "]\n";

					created = true;
				}

				//process face
				//std::cout << "Face: " << line << std::endl;

				curr = nextSubStr(line, delim); //vertex 1
				processVertex(textures, normals, indices, curr, texts, norms);

				curr = nextSubStr(line, delim); //vertex 2
				processVertex(textures, normals, indices, curr, texts, norms);

				curr = nextSubStr(line, delim); //vertex 3
				processVertex(textures, normals, indices, curr, texts, norms);
			}
		}

		inds = new GLuint[indices->size()];

		//TODO: check if reorganization is correct;

		for (unsigned int i = 0; i < indices->size(); i++)
		{
			inds[i] = indices->at(i);
		}

		//CORRECTNESS CHECK
		/*
		std::cout << "-- Testing Vertices --\n";
		for (unsigned int i = 0; i < vertices->size(); i++)
		{
			float x = verts[i * 3], y = verts[i * 3 + 1], z = verts[i * 3 + 2];
			std::cout << "Vector: " << (vertices->at(i)).toString() << " == Array: (" << x << "," << y << "," << z << ")\n";
		}
		std::cout << "-- End Vertices Test --\n-- Testing Textures --\n";
		for (unsigned int i = 0; i < textures->size(); i++)
		{
			float x = texts[i * 2], y = texts[i * 2 + 1];
			std::cout << "Vector: " << (textures->at(i)).toString() << " == Array: (" << x << "," << y << ")\n";
		}
		std::cout << "-- End Textures Test --\n-- Testing Normals --\n";
		for (unsigned int i = 0; i < normals->size(); i++)
		{
			float x = norms[i * 3], y = norms[i * 3 + 1], z = norms[i * 3 + 2];
			std::cout << "Vector: " << (normals->at(i)).toString() << " == Array: (" << x << "," << y << "," << z << ")\n";
		}
		std::cout << "-- End Normals Test --\n-- Testing Indices --\n";
		for (unsigned int i = 0; i < indices->size(); i++)
		{
			std::cout << "Vector: " << indices->at(i) << " == Array: " << inds[i] << std::endl;
		}

		std::cout << "NumIndices: " << indices->size() << std::endl;


		int faceCount = 3, faceNum = 0;

		std::cout << "Testing faces...\n";
		for (unsigned int j = 0; j < indices->size(); j++)
		{
			if (faceCount % 3 == 0)
			{
				faceCount = 0;
				faceNum++;
				std::cout << "Face #" << faceNum << std::endl;
			}
			faceCount++;

			unsigned int i = inds[j];
			Vec3 v(verts[i * 3], verts[i * 3 + 1], verts[i * 3 + 2]);
			Vec2 t(texts[i * 2], texts[i * 2 + 1]);
			Vec3 n(norms[i * 3], norms[i * 3 + 1], norms[i * 3 + 2]);
			std::cout << "v" << v.toString() << " t" << t.toString() << " n" << n.toString() << std::endl;
		}
		*/
		//CORRECTNESS CHECK END

		Model* model = Loader::loadModel(verts, norms, texts, inds, vertices->size(), vertices->size(), vertices->size(), indices->size(), material);

		if (model->getMaterial()->getTextureID() == -1)
			model->getMaterial()->setTextureID(Loader::loadTexture(texturefilepath));

		BoundingBox *boundingBox = new BoundingBox(minx, miny, minz, maxx, maxy, maxz);
		model->setBaseBoundingBox(boundingBox);

		//std::cout << "Model->numIndices: " << model.getNumIndices() << std::endl;

		delete indices;
		delete vertices;
		delete textures;
		delete normals;

		// TODO: Fix this... program crashes when these are deleted
		//delete[] verts;
		//delete[] norms;
		//delete[] texts;
		//delete[] inds;

		file.close();

		return model;
	}

	void ObjectFileLoader::processVertex(std::vector<Vec2> *textures, std::vector<Vec3> *normals, std::vector<GLuint> *indices, std::string vertexStr, GLfloat *texts, GLfloat *norms)
	{
		GLuint vIndex, tIndex, nIndex;

		vIndex = atoi(nextSubStr(vertexStr, "/").c_str()) - 1;
		tIndex = atoi(nextSubStr(vertexStr, "/").c_str()) - 1;
		nIndex = atoi(nextSubStr(vertexStr, "/").c_str()) - 1;

		//std::cout << "vIndex: " << vIndex << " tIndex: " << tIndex << " nIndex: " << nIndex << std::endl;

		indices->push_back(vIndex);

		//Vec3 vertex = vertices->at(vIndex);
		Vec2 texture = textures->at(tIndex);
		Vec3 normal = normals->at(nIndex);

		/*verts[vIndex * 3] = vertex.x;
		verts[vIndex * 3 + 1] = vertex.y;
		verts[vIndex * 3 + 2] = vertex.z;*/
		//std::cout << "Inserted into verts[" << vIndex * 3 + 2 << "]\n";

		//std::cout << "vertices->at(" << vIndex << ") = (" << verts[vIndex * 3] << "," << verts[vIndex * 3 + 1] << "," << verts[vIndex * 3 + 2] << ")\n";

		texts[vIndex * 2] = texture.x;
		texts[vIndex * 2 + 1] = texture.y; //NOTE: May have to 1 - texture.y for this...

		//std::cout << "Inserted into texts[" << vIndex * 2 + 1 << "]\n";
		//std::cout << "textures->at(" << tIndex << ") = (" << texts[tIndex * 2] << "," << texts[tIndex * 2 + 1] << ")\n";

		norms[vIndex * 3] = normal.x;
		norms[vIndex * 3 + 1] = normal.y;
		norms[vIndex * 3 + 2] = normal.z;
		//std::cout << "Inserted into norms[" << vIndex * 3 + 2 << "]\n";
		//std::cout << "normals->at(" << nIndex << ") = (" << norms[nIndex * 3] << "," << norms[nIndex * 3 + 1] << "," << norms[nIndex * 3 + 2] << ")\n";

	}

	Material* ObjectFileLoader::loadMaterial(std::string filepath, std::string texturepath)
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
				sh = atof(curr.c_str());
			}
			else if (curr == "Ka")
			{
				curr = nextSubStr(line, delim);
				a = atof(curr.c_str());
				curr = nextSubStr(line, delim);
				a += atof(curr.c_str());
				curr = nextSubStr(line, delim);
				a += atof(curr.c_str());

				a /= 3;
			}
			else if (curr == "Kd")
			{
				curr = nextSubStr(line, delim);
				d = (float)atof(curr.c_str());
				curr = nextSubStr(line, delim);
				d += (float)atof(curr.c_str());
				curr = nextSubStr(line, delim);
				d += (float)atof(curr.c_str());

				d /= 3;
			}
			else if (curr == "Ks")
			{
				curr = nextSubStr(line, delim);
				s = (float)atof(curr.c_str());
				curr = nextSubStr(line, delim);
				s += (float)atof(curr.c_str());
				curr = nextSubStr(line, delim);
				s += (float)atof(curr.c_str());

				s /= 3;
			}
			else if (curr == "Ke")
			{
				curr = nextSubStr(line, delim);
				e = (float)atof(curr.c_str());
				curr = nextSubStr(line, delim);
				e += (float)atof(curr.c_str());
				curr = nextSubStr(line, delim);
				e += (float)atof(curr.c_str());

				e /= 3;
			}
			else if (curr == "Ni")
			{
				curr = nextSubStr(line, delim);
				ri = (float)atof(curr.c_str());
			}
			else if (curr == "d")
			{
				curr = nextSubStr(line, delim);
				t = (float)atof(curr.c_str());
			}

		}

		materialFile.close();

		Material* material = new Material(filepath.c_str(), name.c_str(), textureID, a, e, d, s, sh, ri, 0.0f, t);

		return material;
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
