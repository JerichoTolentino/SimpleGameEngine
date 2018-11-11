#pragma once
#include "TerrainModel.h"
#include "SpaceModel.h"
#include "TexturePack.h"
#include "Material.h"

namespace SimpleGameEngine::Models
{
	class TerrainRenderModel
	{
	private:
		TerrainModel m_terrainModel;
		Material m_material;
		SpaceModel m_spaceModel;
		TexturePack m_texturePack;
		GLuint m_geometryVaoId;


	public:
		TerrainRenderModel();
		TerrainRenderModel(TerrainModel terrainModel, Material material, SpaceModel spaceModel, TexturePack texturePack, GLuint geometryVaoId);
		TerrainRenderModel(const TerrainRenderModel & other);
		virtual ~TerrainRenderModel();



		TerrainModel getTerrainModel() const;
		Material getMaterial() const;
		SpaceModel getSpaceModel() const;
		TexturePack getTexturePack() const;
		GLuint getGeometryVaoId() const;



		TerrainRenderModel & operator=(const TerrainRenderModel & other);
	};
}
