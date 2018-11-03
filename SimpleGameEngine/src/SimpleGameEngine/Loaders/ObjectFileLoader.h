#pragma once
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>

#include "Loader.h"
#include "../Models/Model.h"
#include "../Models/Material.h"
#include "../Math/Vec2.h"
#include "../Math/Vec3.h"

namespace SimpleGameEngine::Loaders
{
	class ObjectFileLoader
	{
	public:
		ObjectFileLoader();
		~ObjectFileLoader();

		static Models::Model* loadOBJ(std::string filepath, std::string texturefilepath);

	private:
		static Models::Material* loadMaterial(std::string filepath, std::string texturepath);
		static void processVertex(std::vector<Math::Vec2> *textures, std::vector<Math::Vec3> *normals, std::vector<GLuint> *indices, std::string vertex, GLfloat *texts, GLfloat *norms);
	};
}
