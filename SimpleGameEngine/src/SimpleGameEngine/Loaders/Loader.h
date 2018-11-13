#pragma once
#include <GL/glew.h>
#include <SOIL.h>
#include <string>
#include <vector>
#include <memory>

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

		static GLuint loadSkybox(const Models::SkyboxModel & skybox);
		static GLuint loadGeometryModel(const Models::GeometryModel & model);
		static GLuint loadTexture(const std::string & filepath);
		static GLuint loadCubemapTexture(
			const std::string & right, 
			const std::string & left, 
			const std::string & up, 
			const std::string & down, 
			const std::string & back, 
			const std::string & front);

		/// <summary>
		/// Loads an image as a height map.
		/// </summary>
		/// <param name="filepath"></param>
		/// <param name="maxHeight"></param>
		/// <returns></returns>
		static Models::HeightMap loadHeightMap(const std::string & filepath, int maxHeight);

		/// <summary>
		/// Loads a series of textures as a <see cref="TexturePack"/>.
		/// </summary>
		/// <param name="redTexture"></param>
		/// <param name="greenTexture"></param>
		/// <param name="blueTexture"></param>
		/// <param name="backgroundTexture"></param>
		/// <param name="blendMap"></param>
		/// <returns></returns>
		static Models::TexturePack loadTexturePack(
			const std::string & redTextureFile, 
			const std::string & greenTextureFile, 
			const std::string & blueTextureFile, 
			const std::string & backgroundTextureFile, 
			const std::string & blendMapFile);
	};
}
