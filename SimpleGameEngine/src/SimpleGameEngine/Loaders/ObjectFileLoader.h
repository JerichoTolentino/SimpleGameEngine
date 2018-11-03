#pragma once
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>

#include "Loader.h"
#include "../Math/Vec2.h"
#include "../Math/Vec3.h"

using namespace SimpleGameEngine::Math;

namespace SimpleGameEngine::Loaders
{
	class ObjectFileLoader
	{
	public:
		ObjectFileLoader();
		~ObjectFileLoader();

		static Model* loadOBJ(std::string filepath, std::string texturefilepath);

	private:
		static Material* loadMaterial(std::string filepath, std::string texturepath);
		static void processVertex(std::vector<Vec2> *textures, std::vector<Vec3> *normals, std::vector<GLuint> *indices, std::string vertex, GLfloat *texts, GLfloat *norms);
	};
}
