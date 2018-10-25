#pragma once
#include <GL/glew.h>
#include "../loaders/Loader.h"

#define SIZE 500

class Skybox
{
private:
	GLuint vaoID;
	GLuint textureID;
	int numIndices;
public:
	Skybox();
	~Skybox();

	Skybox(const char* right, const char* left, const char* up, const char* down, const char* back, const char* front);

	GLuint getVAO() const;
	GLuint getTextureID() const;
	int getNumIndices() const;

	std::string toString() const;

private:
	GLuint initVertices();
};

