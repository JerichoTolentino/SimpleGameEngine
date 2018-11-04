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

		static void loadSkybox(std::vector<Math::Vec3> vertices, std::vector<Math::Vec2> textureUvs, std::vector<GLuint> indices);
		static void loadModel(GeometryModel model);
		static void loadMaterial(Material material);

		//static GLuint loadSkybox(GLfloat vertices[], GLfloat textures[], GLuint indices[], int numVertices, int numTextures, int numIndices);
		//static Models::GeometryModel* loadModel(GLfloat vertices[], GLuint indices[], int numVertices, int numIndices);
		//static Models::GeometryModel* loadModel(GLfloat vertices[], GLfloat normals[], GLuint indices[], int numVertices, int numNormals, int numIndices);
		//static Models::GeometryModel* loadModel(GLfloat vertices[], GLfloat normals[], GLfloat textures[], GLuint indices[], int numVertices, int numNormals, int numTextures, int numIndices);
		//static Models::GeometryModel* loadModel(GLfloat vertices[], GLfloat normals[], GLfloat textures[], GLuint indices[], int numVertices, int numNormals, int numTextures, int numIndices, Models::Material* material);
		//static Models::Material* loadMaterial(std::string textureFile, std::string name, float ambient, float emissive, float diffuse, float specular, float specularHighlight, float refractiveIndex, float reflectivity, float transparency);
		static GLuint loadTexture(std::string filepath);
		static GLuint loadCubemapTexture(std::string right, std::string left, std::string up, std::string down, std::string back, std::string front);
	};
}
