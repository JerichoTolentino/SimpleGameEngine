#pragma once
#include <GL/glew.h>
#include <SOIL.h>
#include <iostream>
#include "../entities/Model.h"
#include "../utils/MessageHandler.h"

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
	static Material* loadMaterial(const char* textureFile, const char* name, float ambient, float emissive, float diffuse, float specular, float specularHighlight, float refractiveIndex, float reflectivity, float transparency);
	static GLuint loadTexture(const char* filepath);
	static GLuint loadCubemapTexture(const char* right, const char* left, const char* up, const char* down, const char* back, const char* front);
};

