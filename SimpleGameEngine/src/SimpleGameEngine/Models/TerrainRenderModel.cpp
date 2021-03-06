#include "sgepch.h"
#include "TerrainRenderModel.h"

namespace SimpleGameEngine::Models
{
	TerrainRenderModel::TerrainRenderModel()
	{
	}

	TerrainRenderModel::TerrainRenderModel(
		const std::shared_ptr<TerrainModel> terrainModel, 
		const std::shared_ptr<Material> material, 
		const std::shared_ptr<SpaceModel> spaceModel, 
		const std::shared_ptr<TexturePack> texturePack, 
		GLuint geometryVaoId)
	{
		m_terrainModel = terrainModel;
		m_material = material;
		m_spaceModel = spaceModel;
		m_texturePack = texturePack;
		m_geometryVaoId = geometryVaoId;
	}

	TerrainRenderModel::TerrainRenderModel(const TerrainRenderModel & other)
		: TerrainRenderModel(other.m_terrainModel, other.m_material, other.m_spaceModel, other.m_texturePack, other.m_geometryVaoId)
	{
	}

	TerrainRenderModel::~TerrainRenderModel()
	{
	}



	std::shared_ptr<TerrainModel> TerrainRenderModel::getTerrainModel() const
	{
		return m_terrainModel;
	}

	std::shared_ptr<Material> TerrainRenderModel::getMaterial() const
	{
		return m_material;
	}

	std::shared_ptr<SpaceModel> TerrainRenderModel::getSpaceModel() const
	{
		return m_spaceModel;
	}

	std::shared_ptr<TexturePack> TerrainRenderModel::getTexturePack() const
	{
		return m_texturePack;
	}

	GLuint TerrainRenderModel::getGeometryVaoId() const
	{
		return m_geometryVaoId;
	}



	TerrainRenderModel & TerrainRenderModel::operator=(const TerrainRenderModel & other)
	{
		m_terrainModel = other.m_terrainModel;
		m_spaceModel = other.m_spaceModel;
		m_texturePack = other.m_texturePack;
		m_material = other.m_material;
		m_geometryVaoId = other.m_geometryVaoId;

		return *this;
	}
}
