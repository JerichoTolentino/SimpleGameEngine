#pragma once
#include <vector>
#include <GL/glew.h>
#include "../Models/GeometryModel.h"
#include "../Models/Material.h"
#include "../Math/Vec3.h"
#include "../Math/Vec2.h"

namespace SimpleGameEngine::Loaders
{
	class ObjectFileLoader
	{
	public:
		ObjectFileLoader();
		~ObjectFileLoader();

		static Models::GeometryModel loadObjFile(std::string filepath, std::string texturefilepath);

	private:
		static Models::Material loadMaterial(std::string filepath, std::string texturepath);
		static void processVertex(std::vector<Math::Vec2> textures, std::vector<Math::Vec3> normals, std::vector<GLuint> indices, std::string vertex, std::vector<Math::Vec2> texts, std::vector<Math::Vec3> norms);
	};
}
