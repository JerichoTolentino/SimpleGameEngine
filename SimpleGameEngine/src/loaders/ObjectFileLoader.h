#pragma once
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include "Loader.h"
#include "../math/engineMath.h"
#include "../entities/Model.h"

class ObjectFileLoader
{
public:
	ObjectFileLoader();
	~ObjectFileLoader();

	static Model* loadOBJ(const char* filepath, const char* texturefilepath);

private:
	static Material* loadMaterial(std::string filepath, const char* texturepath);
	static void processVertex(std::vector<Vec2> *textures, std::vector<Vec3> *normals, std::vector<GLuint> *indices, std::string vertex, GLfloat *texts, GLfloat *norms);
};

