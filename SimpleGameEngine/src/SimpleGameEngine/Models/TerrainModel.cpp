#include "sgepch.h"
#include "TerrainModel.h"

using namespace SimpleGameEngine::Math;

namespace SimpleGameEngine::Models
{
	TerrainModel::TerrainModel()
	{
	}

	TerrainModel::TerrainModel(
		const std::shared_ptr<GeometryModel> geometryModel, 
		const std::shared_ptr<HeightMap> heightMap, 
		int tileSize, 
		int tileFactor, 
		int rowCount, 
		int columnCount)
	{
		m_geometryModel = geometryModel;
		m_heightMap = heightMap;
		m_tileSize = tileSize;
		m_tileFactor = tileFactor;
		m_rowCount = rowCount;
		m_columnCount = columnCount;
	}

	TerrainModel::TerrainModel(const TerrainModel & other)
		: TerrainModel(other.m_geometryModel, other.m_heightMap, other.m_tileSize, other.m_tileFactor, other.m_rowCount, other.m_columnCount)
	{
	}

	TerrainModel::~TerrainModel()
	{
	}



	std::shared_ptr<GeometryModel> TerrainModel::getGeometryModel() const
	{
		return m_geometryModel;
	}

	std::shared_ptr<HeightMap> TerrainModel::getHeightMap() const
	{
		return m_heightMap;
	}

	int TerrainModel::getTileSize() const
	{
		return m_tileSize;
	}

	int TerrainModel::getTileFactor() const
	{
		return m_tileFactor;
	}

	int TerrainModel::getRowCount() const
	{
		return m_rowCount;
	}

	int TerrainModel::getColumnCount() const
	{
		return m_columnCount;
	}

	TerrainModel & TerrainModel::operator=(const TerrainModel & other)
	{
		m_geometryModel = other.m_geometryModel;
		m_heightMap = other.m_heightMap;
		m_tileSize = other.m_tileSize;
		m_tileFactor = other.m_tileFactor;
		m_rowCount = other.m_rowCount;
		m_columnCount = other.m_columnCount;

		return *this;
	}

	TerrainModel TerrainModel::GenerateTerrainModel(int tileSize, int tileFactor, const std::shared_ptr<HeightMap> heightMap)
	{
		int rows = heightMap->getWidth() - 1;
		int cols = heightMap->getHeight() - 1;
		int totalVertices = rows * cols * 4;
		int totalIndices = rows * cols * 6;

		auto vertices = std::make_shared<std::vector<Vec3>>();
		vertices->reserve(totalVertices);
		auto normals = std::make_shared<std::vector<Vec3>>();
		normals->reserve(totalVertices);
		auto textureUvs = std::make_shared<std::vector<Vec2>>();
		textureUvs->reserve(totalVertices);
		auto indices = std::make_shared<std::vector<unsigned int>>();
		indices->reserve(totalIndices);

		// Calculate vertices, normals, and texture uvs
		for (int row = 0; row <= rows; row++)
		{
			for (int col = 0; col <= cols; col++)
			{
				float x, y, z, u, v;

				// Calculate vertex
				x = col * tileSize;
				z = row * tileSize;
				y = heightMap->findHeightAt(x, z);
				vertices->push_back(Vec3(x, y, z));

				// Calculate normal
				x = 0;
				y = 1;
				z = 0;
				normals->push_back(Vec3(x, y, z));

				// Calculate texture uv
				u = (float) col / (float) cols;
				v = (float) row / (float) rows;
				textureUvs->push_back(Vec2(u, v));
			}
		}

		// Calculate indices
		for (int row = 0; row < rows; row++)
		{
			for (int col = 0; col < cols; col++)
			{
				unsigned int topLeft = row * cols + col + row;
				unsigned int topRight = topLeft + 1;
				unsigned int bottomLeft = (row + 1) * cols + col + row + 1;
				unsigned int bottomRight = bottomLeft + 1;

				// Add indices to form 2 CCW triangles making a square
				indices->push_back(topLeft);
				indices->push_back(bottomLeft);
				indices->push_back(bottomRight);

				indices->push_back(bottomRight);
				indices->push_back(topRight);
				indices->push_back(topLeft);
			}
		}
		return TerrainModel(std::make_shared<GeometryModel>(vertices, textureUvs, normals, indices), heightMap, tileSize, tileFactor,  rows, cols);
	}

}
