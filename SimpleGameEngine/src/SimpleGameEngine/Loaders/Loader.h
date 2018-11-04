#pragma once
#include <GL/glew.h>
#include <SOIL.h>
#include <string>
#include <vector>

#include "../Models/Material.h"
#include "../Models/GeometryModel.h"


namespace SimpleGameEngine::Loaders
{
	class Loader
	{
	public:

		static GLuint loadSkybox(std::vector<Math::Vec3> vertices, std::vector<Math::Vec2> textureUvs, std::vector<GLuint> indices);
		static GLuint loadGeometryModel(GeometryModel model);
		static GLuint loadTexture(std::string filepath);
		static GLuint loadCubemapTexture(std::string right, std::string left, std::string up, std::string down, std::string back, std::string front);
	};
}
