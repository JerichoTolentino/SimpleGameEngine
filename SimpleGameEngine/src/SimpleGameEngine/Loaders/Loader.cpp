#include "Loader.h"
#include "TextureLoadException.h"
#include "../Utility/Generic.h"

#define VERTICES_ATTR 0
#define NORMALS_ATTR 1
#define TEXTURES_ATTR 2

using namespace SimpleGameEngine::Models;
using namespace SimpleGameEngine::Utility;
using namespace SimpleGameEngine::Math;

namespace SimpleGameEngine::Loaders
{

	GLuint Loader::loadSkybox(std::vector<Math::Vec3> vertices, std::vector<Math::Vec2> textureUvs, std::vector<GLuint> indices)
	{
		// Flatten vectors
		std::vector<float> flattenedVertices = Generic::flatten(vertices.begin(), vertices.end(), (std::function<std::vector<float>(Vec3)>) [](Vec3 vec)
		{
			std::vector<float> unpacked;
			unpacked.push_back(vec.x);
			unpacked.push_back(vec.y);
			unpacked.push_back(vec.z);
			return unpacked;
		});
		std::vector<float> flattenedUvs = Generic::flatten(textureUvs.begin(), textureUvs.end(), (std::function<std::vector<float>(Vec2)>) [](Vec2 vec)
		{
			std::vector<float> unpacked;
			unpacked.push_back(vec.x);
			unpacked.push_back(vec.y);
			return unpacked;
		});
		std::vector<GLuint> flattenedIndices = Generic::flatten(indices.begin(), indices.end(), (std::function<std::vector<GLuint>(Vec3)>) [](Vec3 vec)
		{
			std::vector<GLuint> unpacked;
			unpacked.push_back((GLuint) vec.x);
			unpacked.push_back((GLuint) vec.y);
			unpacked.push_back((GLuint) vec.z);
			return unpacked;
		});

		// Load into OpenGL
		GLuint vao, vbo;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Bind indices
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * flattenedIndices.size(), Generic::toArray(flattenedIndices), GL_STATIC_DRAW);

		// Bind vertices
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * flattenedVertices.size(), Generic::toArray(flattenedVertices), GL_STATIC_DRAW);
		glVertexAttribPointer(VERTICES_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Bind texture UVs
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * flattenedUvs.size(), Generic::toArray(flattenedUvs), GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURES_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		return vao;
	}

	GLuint Loader::loadGeometryModel(GeometryModel model)
	{
		// Flatten vectors
		std::vector<float> flattenedVertices = Generic::flatten(model.getVertices().begin(), model.getVertices().end(), (std::function<std::vector<float>(Vec3)>) [](Vec3 vec)
		{
			std::vector<float> unpacked;
			unpacked.push_back(vec.x);
			unpacked.push_back(vec.y);
			unpacked.push_back(vec.z);
			return unpacked;
		});
		std::vector<float> flattenedNormals = Generic::flatten(model.getNormals().begin(), model.getNormals().end(), (std::function<std::vector<float>(Vec3)>) [](Vec3 vec)
		{
			std::vector<float> unpacked;
			unpacked.push_back(vec.x);
			unpacked.push_back(vec.y);
			unpacked.push_back(vec.z);
			return unpacked;
		});
		std::vector<float> flattenedUvs = Generic::flatten(model.getTextureUvs().begin(), model.getTextureUvs().end(), (std::function<std::vector<float>(Vec2)>) [](Vec2 vec)
		{
			std::vector<float> unpacked;
			unpacked.push_back(vec.x);
			unpacked.push_back(vec.y);
			return unpacked;
		});
		std::vector<GLuint> flattenedIndices = Generic::flatten(model.getIndices().begin(), model.getIndices().end(), (std::function<std::vector<GLuint>(Vec3)>) [](Vec3 vec)
		{
			std::vector<GLuint> unpacked;
			unpacked.push_back((GLuint)vec.x);
			unpacked.push_back((GLuint)vec.y);
			unpacked.push_back((GLuint)vec.z);
			return unpacked;
		});

		// Load into OpenGL
		GLuint vao, vbo;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Bind indices
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * flattenedIndices.size(), Generic::toArray(flattenedIndices), GL_STATIC_DRAW);

		// Bind vertices
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * flattenedVertices.size(), Generic::toArray(flattenedVertices), GL_STATIC_DRAW);
		glVertexAttribPointer(VERTICES_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Bind normals
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * flattenedNormals.size(), Generic::toArray(flattenedNormals), GL_STATIC_DRAW);
		glVertexAttribPointer(NORMALS_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Bind texture UVs
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * flattenedUvs.size(), Generic::toArray(flattenedUvs), GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURES_ATTR, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
		return vao;
	}

	GLuint Loader::loadTexture(std::string filepath)
	{
		GLuint id = SOIL_load_OGL_texture(filepath.c_str(), 0, 0, SOIL_FLAG_INVERT_Y);
		if (id < 0)
			throw TextureLoadException("Failed to load texture: " + filepath);

		glBindTexture(GL_TEXTURE_2D, id);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glBindTexture(GL_TEXTURE_2D, 0);

		return id;
	}

	GLuint Loader::loadCubemapTexture(std::string right, std::string left, std::string up, std::string down, std::string back, std::string front)
	{
		GLuint id = SOIL_load_OGL_cubemap(right.c_str(), left.c_str(), up.c_str(), down.c_str(), back.c_str(), front.c_str(), 0, 0, 0);
		if (id < 0)
			throw TextureLoadException("Failed to load cubemap texture");

		glBindTexture(GL_TEXTURE_CUBE_MAP, id);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		return id;
	}
}
