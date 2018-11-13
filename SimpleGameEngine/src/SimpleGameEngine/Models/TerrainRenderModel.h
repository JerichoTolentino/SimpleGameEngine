#pragma once
#include <memory>
#include "TerrainModel.h"
#include "SpaceModel.h"
#include "TexturePack.h"
#include "Material.h"

namespace SimpleGameEngine::Models
{
	class TerrainRenderModel
	{
	private:
		std::shared_ptr<TerrainModel> m_terrainModel;
		std::shared_ptr<Material> m_material;
		std::shared_ptr<SpaceModel> m_spaceModel;
		std::shared_ptr<TexturePack> m_texturePack;
		GLuint m_geometryVaoId;


	public:
		TerrainRenderModel();
		TerrainRenderModel(
			const std::shared_ptr<TerrainModel> terrainModel, 
			const std::shared_ptr<Material> material, 
			const std::shared_ptr<SpaceModel> spaceModel, 
			const std::shared_ptr<TexturePack> texturePack, 
			GLuint geometryVaoId);
		TerrainRenderModel(const TerrainRenderModel & other);
		virtual ~TerrainRenderModel();



		std::shared_ptr<TerrainModel> getTerrainModel() const;
		std::shared_ptr<Material> getMaterial() const;
		std::shared_ptr<SpaceModel> getSpaceModel() const;
		std::shared_ptr<TexturePack> getTexturePack() const;
		GLuint getGeometryVaoId() const;



		TerrainRenderModel & operator=(const TerrainRenderModel & other);
	};
}
