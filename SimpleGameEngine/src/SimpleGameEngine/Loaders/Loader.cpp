#include "Loader.h"
#include "TextureLoadException.h"

#define VERTICES_ATTR 0
#define NORMALS_ATTR 1
#define TEXTURES_ATTR 2

using namespace SimpleGameEngine::Models;

namespace SimpleGameEngine::Loaders
{
	Loader::Loader()
	{
	}


	Loader::~Loader()
	{
	}

	GLuint Loader::loadSkybox(GLfloat vertices[], GLfloat textures[], GLuint indices[], int numVertices, int numTextures, int numIndices)
	{
		GLuint vao, vbo;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * numIndices, indices, GL_STATIC_DRAW);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 3, vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(VERTICES_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numTextures * 3, textures, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURES_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		return vao;
	}

	Model* Loader::loadModel(GLfloat vertices[], GLuint indices[], int numVertices, int numIndices)
	{
		GLuint vao, vbo;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * numIndices, indices, GL_STATIC_DRAW);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 3, vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(VERTICES_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		return new Model(vao, numIndices);
	}

	Model* Loader::loadModel(GLfloat vertices[], GLfloat normals[], GLuint indices[], int numVertices, int numNormals, int numIndices)
	{
		GLuint vao, vbo;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * numIndices, indices, GL_STATIC_DRAW);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 3, vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(VERTICES_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numNormals * 3, normals, GL_STATIC_DRAW);
		glVertexAttribPointer(NORMALS_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		return new Model(vao, numIndices);
	}

	Model* Loader::loadModel(GLfloat vertices[], GLfloat normals[], GLfloat textures[], GLuint indices[], int numVertices, int numNormals, int numTextures, int numIndices)
	{
		GLuint vao, vbo;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * numIndices, indices, GL_STATIC_DRAW);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 3, vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(VERTICES_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numNormals * 3, normals, GL_STATIC_DRAW);
		glVertexAttribPointer(NORMALS_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numTextures * 2, textures, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURES_ATTR, 2, GL_FLOAT, GL_FALSE, 0, 0);

		return new Model(vao, numIndices);
	}

	Model* Loader::loadModel(GLfloat vertices[], GLfloat normals[], GLfloat textures[], GLuint indices[], int numVertices, int numNormals, int numTextures, int numIndices, Material* material)
	{
		GLuint vao, vbo;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * numIndices, indices, GL_STATIC_DRAW);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numVertices * 3, vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(VERTICES_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numNormals * 3, normals, GL_STATIC_DRAW);
		glVertexAttribPointer(NORMALS_ATTR, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numTextures * 2, textures, GL_STATIC_DRAW);
		glVertexAttribPointer(TEXTURES_ATTR, 2, GL_FLOAT, GL_FALSE, 0, 0);

		return new Model(vao, numIndices, material);
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

	Material* Loader::loadMaterial(std::string textureFile, std::string name, float ambient, float emissive, float diffuse, float specular, float specularHighlight, float refractiveIndex, float reflectivity, float transparency)
	{
		GLuint textureID = loadTexture(textureFile);
		return new Material(textureFile, name, textureID, ambient, emissive, diffuse, specular, specularHighlight, refractiveIndex, reflectivity, transparency);
	}
}
