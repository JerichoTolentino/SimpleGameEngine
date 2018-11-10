#pragma once
#include "TerrainModel.h"
#include "SpaceModel.h"
#include "TexturePack.h"

namespace SimpleGameEngine::Models
{
	class TerrainRenderModel
	{
	private:
		TerrainModel m_terrainModel;
		SpaceModel m_spaceModel;
		TexturePack m_texturePack;
		GLuint m_geometryVaoId;


	public:
		TerrainRenderModel();
		TerrainRenderModel(TerrainModel terrainModel, SpaceModel spaceModel, TexturePack texturePack);
		TerrainRenderModel(const TerrainRenderModel & other);
		virtual ~TerrainRenderModel();



		TerrainModel getTerrainModel() const;
		SpaceModel getSpaceModel() const;
		TexturePack getTexturePack() const;
		GLuint getGeometryVaoId() const;
	};
}
