#pragma once
#include <GL/glew.h>
#include <SOIL.h>
#include <iostream>
#include <string>


namespace SimpleGameEngine::Loaders
{
	class Loader
	{
	public:
		Loader();
		~Loader();

		static GLuint loadSkybox(GLfloat vertices[], GLfloat textures[], GLuint indices[], int numVertices, int numTextures, int numIndices);
		static Model* loadModel(GLfloat vertices[], GLuint indices[], int numVertices, int numIndices);
		static Model* loadModel(GLfloat vertices[], GLfloat normals[], GLuint indices[], int numVertices, int numNormals, int numIndices);
		static Model* loadModel(GLfloat vertices[], GLfloat normals[], GLfloat textures[], GLuint indices[], int numVertices, int numNormals, int numTextures, int numIndices);
		static Model* loadModel(GLfloat vertices[], GLfloat normals[], GLfloat textures[], GLuint indices[], int numVertices, int numNormals, int numTextures, int numIndices, Material* material);
		static Material* loadMaterial(std::string textureFile, std::string name, float ambient, float emissive, float diffuse, float specular, float specularHighlight, float refractiveIndex, float reflectivity, float transparency);
		static GLuint loadTexture(std::string filepath);
		static GLuint loadCubemapTexture(std::string right, std::string left, std::string up, std::string down, std::string back, std::string front);
	};
}
