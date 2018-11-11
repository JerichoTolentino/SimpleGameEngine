#pragma once
#include <GL/glew.h>
#include <SOIL.h>
#include <string>
#include <vector>

#include "../Models/Material.h"
#include "../Models/GeometryModel.h"
#include "../Models/SkyboxModel.h"
#include "../Models/HeightMap.h"
#include "../Models/TexturePack.h"


namespace SimpleGameEngine::Loaders
{
	class Loader
	{
	public:

		static GLuint loadSkybox(Models::SkyboxModel skybox);
		static GLuint loadGeometryModel(Models::GeometryModel model);
		static GLuint loadTexture(std::string filepath);
		static GLuint loadCubemapTexture(std::string right, std::string left, std::string up, std::string down, std::string back, std::string front);

		/// <summary>
		/// Loads an image as a height map.
		/// </summary>
		/// <param name="filepath"></param>
		/// <param name="maxHeight"></param>
		/// <returns></returns>
		static Models::HeightMap loadHeightMap(std::string filepath, int maxHeight);

		/// <summary>
		/// Loads a series of textures as a <see cref="TexturePack"/>.
		/// </summary>
		/// <param name="redTexture"></param>
		/// <param name="greenTexture"></param>
		/// <param name="blueTexture"></param>
		/// <param name="backgroundTexture"></param>
		/// <param name="blendMap"></param>
		/// <returns></returns>
		static Models::TexturePack loadTexturePack(std::string redTextureFile, std::string greenTextureFile, std::string blueTextureFile, std::string backgroundTextureFile, std::string blendMapFile);
	};
}
