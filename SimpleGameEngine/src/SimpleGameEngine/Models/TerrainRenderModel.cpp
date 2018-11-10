#include "TerrainRenderModel.h"

namespace SimpleGameEngine::Models
{
	TerrainRenderModel::TerrainRenderModel()
	{
	}

	TerrainRenderModel::TerrainRenderModel(TerrainModel terrainModel, Material material, SpaceModel spaceModel, TexturePack texturePack)
	{
		m_terrainModel = terrainModel;
		m_material = material;
		m_spaceModel = spaceModel;
		m_texturePack = texturePack;
	}

	TerrainRenderModel::TerrainRenderModel(const TerrainRenderModel & other)
		: TerrainRenderModel(other.m_terrainModel, other.m_material, other.m_spaceModel, other.m_texturePack)
	{
	}

	TerrainRenderModel::~TerrainRenderModel()
	{
	}



	TerrainModel TerrainRenderModel::getTerrainModel() const
	{
		return m_terrainModel;
	}

	Material TerrainRenderModel::getMaterial() const
	{
		return m_material;
	}

	SpaceModel TerrainRenderModel::getSpaceModel() const
	{
		return m_spaceModel;
	}

	TexturePack TerrainRenderModel::getTexturePack() const
	{
		return m_texturePack;
	}
	GLuint TerrainRenderModel::getGeometryVaoId() const
	{
		return m_geometryVaoId;
	}
}
