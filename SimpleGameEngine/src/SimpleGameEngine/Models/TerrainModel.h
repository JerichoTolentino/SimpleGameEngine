#pragma once
#include <memory>
#include "GeometryModel.h"
#include "SpaceModel.h"
#include "HeightMap.h"

namespace SimpleGameEngine::Models
{
	class TerrainModel
	{
	private:
		std::shared_ptr<GeometryModel> m_geometryModel;
		std::shared_ptr<HeightMap> m_heightMap;
		int m_tileSize;
		int m_tileFactor;
		int m_rowCount;
		int m_columnCount;

	public:
		TerrainModel();
		TerrainModel(const std::shared_ptr<GeometryModel> geometryModel, const std::shared_ptr<HeightMap> heightMap, int tileSize, int tileFactor, int rowCount, int columnCount);
		TerrainModel(const TerrainModel & other);
		virtual ~TerrainModel();



		std::shared_ptr<GeometryModel> getGeometryModel() const;
		std::shared_ptr<HeightMap> getHeightMap() const;
		int getTileSize() const;
		int getTileFactor() const;
		int getRowCount() const;
		int getColumnCount() const;



		TerrainModel & operator=(const TerrainModel & other);



		static TerrainModel GenerateTerrainModel(int tileSize, int tileFactor, const std::shared_ptr<HeightMap> heightMap);
	};
}
