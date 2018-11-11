#pragma once
#include "GeometryModel.h"
#include "SpaceModel.h"
#include "HeightMap.h"

namespace SimpleGameEngine::Models
{
	class TerrainModel
	{
	private:
		GeometryModel m_geometryModel;
		HeightMap m_heightMap;
		int m_tileSize;
		int m_rowCount;
		int m_columnCount;

	public:
		TerrainModel();
		TerrainModel(GeometryModel geometryModel, HeightMap heightMap, int tileSize, int rowCount, int columnCount);
		TerrainModel(const TerrainModel & other);
		virtual ~TerrainModel();



		GeometryModel getGeometryModel() const;
		HeightMap getHeightMap() const;
		int getTileSize() const;
		int getRowCount() const;
		int getColumnCount() const;



		TerrainModel & operator=(const TerrainModel & other);



		static TerrainModel GenerateTerrainModel(int tileSize, int rowCount, int columnCount, HeightMap heightMap);
	};
}
