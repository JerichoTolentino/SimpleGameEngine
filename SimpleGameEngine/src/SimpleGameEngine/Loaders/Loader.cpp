#include "Loader.h"
#include "TextureLoadException.h"
#include "../Utility/Generic.h"
#include "../Log.h"

#define VERTICES_ATTR 0
#define NORMALS_ATTR 1
#define TEXTURES_ATTR 2

using namespace SimpleGameEngine::Models;
using namespace SimpleGameEngine::Utility;
using namespace SimpleGameEngine::Math;

namespace SimpleGameEngine::Loaders
{

	GLuint Loader::loadSkybox(Models::SkyboxModel skybox)
	{
		std::vector<Vec3> vertices = skybox.getVertices();
		std::vector<Vec3> textureUvs = skybox.getTextureUvs();

		// Flatten vectors
		std::vector<float> flattenedVertices = Generic::flatten(vertices.begin(), vertices.end(), (std::function<std::vector<float>(Vec3)>) [](Vec3 vec)
		{
			std::vector<float> unpacked;
			unpacked.push_back(vec.x);
			unpacked.push_back(vec.y);
			unpacked.push_back(vec.z);
			return unpacked;
		});
		std::vector<float> flattenedUvs = Generic::flatten(textureUvs.begin(), textureUvs.end(), (std::function<std::vector<float>(Vec3)>) [](Vec3 vec)
		{
			std::vector<float> unpacked;
			unpacked.push_back(vec.x);
			unpacked.push_back(vec.y);
			unpacked.push_back(vec.z);
			return unpacked;
		});

		// Load into OpenGL
		GLuint vao, vbo;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Bind indices
		GLuint * indicesArray = Generic::toArray(skybox.getIndices());
		GLsizeiptr numIndices = sizeof(GLuint) * skybox.getIndices().size();
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices, indicesArray, GL_STATIC_DRAW);

		// Bind vertices
		GLfloat * verticesArray = Generic::toArray(flattenedVertices);
		GLsizeiptr numVertices = sizeof(GLfloat) * flattenedVertices.size();
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, numVertices, verticesArray, GL_STATIC_DRAW);
		glVertexAttribPointer(VERTICES_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Bind texture UVs
		GLfloat * textureUvsArray = Generic::toArray(flattenedUvs);
		GLsizeiptr numTextureUvs = sizeof(GLfloat) * flattenedUvs.size();
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, numTextureUvs, textureUvsArray, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURES_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		SGE_CORE_TRACE("Loaded SkyboxModel with {0} vertices, {1} textureUvs, and {2} indices", numVertices, numTextureUvs, numIndices);

		return vao;
	}

	GLuint Loader::loadGeometryModel(GeometryModel model)
	{
		// Flatten vectors
		auto vertices = model.getVertices();
		std::vector<float> flattenedVertices = Generic::flatten(vertices.begin(), vertices.end(), (std::function<std::vector<float>(Vec3)>) [](Vec3 vec)
		{
			std::vector<float> unpacked;
			unpacked.push_back(vec.x);
			unpacked.push_back(vec.y);
			unpacked.push_back(vec.z);
			return unpacked;
		});
		auto normals = model.getNormals();
		std::vector<float> flattenedNormals = Generic::flatten(normals.begin(), normals.end(), (std::function<std::vector<float>(Vec3)>) [](Vec3 vec)
		{
			std::vector<float> unpacked;
			unpacked.push_back(vec.x);
			unpacked.push_back(vec.y);
			unpacked.push_back(vec.z);
			return unpacked;
		});
		auto textureUvs = model.getTextureUvs();
		std::vector<float> flattenedUvs = Generic::flatten(textureUvs.begin(), textureUvs.end(), (std::function<std::vector<float>(Vec2)>) [](Vec2 vec)
		{
			std::vector<float> unpacked;
			unpacked.push_back(vec.x);
			unpacked.push_back(vec.y);
			return unpacked;
		});

		// Load into OpenGL
		GLuint vao, vbo;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Bind indices
		GLuint * indicesArray = Generic::toArray(model.getIndices());
		GLsizeiptr numIndices = sizeof(GLuint) * model.getIndices().size();
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices, indicesArray, GL_STATIC_DRAW);
		
		// Bind vertices
		GLfloat * verticesArray = Generic::toArray(flattenedVertices);
		GLsizeiptr numVertices = sizeof(GLfloat) * flattenedVertices.size();
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, numVertices, verticesArray, GL_STATIC_DRAW);
		glVertexAttribPointer(VERTICES_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Bind normals
		GLfloat * normalsArray = Generic::toArray(flattenedNormals);
		GLsizeiptr numNormals = sizeof(GLfloat) * flattenedNormals.size();
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, numNormals, normalsArray, GL_STATIC_DRAW);
		glVertexAttribPointer(NORMALS_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// Bind texture UVs
		GLfloat * textureUvsArray = Generic::toArray(flattenedUvs);
		GLsizeiptr numTextureUvs = sizeof(GLfloat) * flattenedUvs.size();
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, numTextureUvs, textureUvsArray, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURES_ATTR, 2, GL_FLOAT, GL_FALSE, 0, 0);

		SGE_CORE_TRACE("Loaded GeometryModel with {0} vertices, {1} normals, {2} textureUvs, and {3} indices", numVertices, numNormals, numTextureUvs, numIndices);
	
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

	Models::HeightMap Loader::loadHeightMap(std::string filepath, int maxHeight)
	{
		int width = 0;
		int height = 0;
		int channels = 0;

		unsigned char * pixels = SOIL_load_image(filepath.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
		
		return HeightMap(Generic::toVector(pixels, width * height * channels), width, height, channels, maxHeight);
	}

	Models::TexturePack Loader::loadTexturePack(std::string redTextureFile, std::string greenTextureFile, std::string blueTextureFile, std::string backgroundTextureFile, std::string blendMapFile)
	{
		GLuint redTextureId = loadTexture(redTextureFile);
		GLuint greenTextureId = loadTexture(greenTextureFile);
		GLuint blueTextureId = loadTexture(blueTextureFile);
		GLuint backgroundTextureId = loadTexture(backgroundTextureFile);
		GLuint blendMapTextureId = loadTexture(blendMapFile);

		return TexturePack(redTextureId, greenTextureId, blueTextureId, backgroundTextureId, blendMapTextureId);
	}


}
