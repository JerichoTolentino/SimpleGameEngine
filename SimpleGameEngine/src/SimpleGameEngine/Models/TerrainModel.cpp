#include "TerrainModel.h"
#include "../Math/Vec3.h"
#include "../Math/Vec2.h"

using namespace SimpleGameEngine::Math;

namespace SimpleGameEngine::Models
{
	TerrainModel::TerrainModel()
	{
	}

	TerrainModel::TerrainModel(GeometryModel geometryModel, HeightMap heightMap, int tileSize, int rowCount, int columnCount)
	{
		m_geometryModel = geometryModel;
		m_heightMap = heightMap;
		m_tileSize = tileSize;
		m_rowCount = rowCount;
		m_columnCount = columnCount;
	}

	TerrainModel::TerrainModel(const TerrainModel & other)
		: TerrainModel(other.m_geometryModel, other.m_heightMap, other.m_tileSize, other.m_rowCount, other.m_columnCount)
	{
	}

	TerrainModel::~TerrainModel()
	{
	}



	GeometryModel TerrainModel::getGeometryModel() const
	{
		return m_geometryModel;
	}

	HeightMap TerrainModel::getHeightMap() const
	{
		return m_heightMap;
	}

	int TerrainModel::getTileSize() const
	{
		return m_tileSize;
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
		m_rowCount = other.m_rowCount;
		m_columnCount = other.m_columnCount;

		return *this;
	}


	// TODO: Test that this actually works (kinda blindly refactored)
	TerrainModel TerrainModel::GenerateTerrainModel(int tileSize, int rowCount, int columnCount, HeightMap heightMap)
	{
		float fRows = rowCount;
		float fCols = columnCount;
		float rowEdge = (float) (rowCount * tileSize);	// Used when calculating z-coordinate for winding (since -z is forwards)

		std::vector<Vec3> vertices;
		std::vector<Vec3> normals; // TODO: These normals are all set to point Y-up for now
		std::vector<Vec2> textureUvs;
		std::vector<unsigned int> indices;

		for (int row = 0; row < rowCount; row++)
		{
			for (int col = 0; col < columnCount; col++)
			{
				int tileOffset = col * 4 + row * 4 * columnCount;
				float x, y, z, u, v;

				// Calculates 4 vertices

				// Bottom left
				x = (float) (col * tileSize);
				z = (float) (rowEdge - row * tileSize);
				y = (float) (heightMap.findHeightAt(x, z));
				vertices.push_back(Vec3(x, y, z));

				// Bottom right
				x = (float) ((col + 1) * tileSize);
				z = (float) (rowEdge - row * tileSize);
				y = (float) (heightMap.findHeightAt(x, z));
				vertices.push_back(Vec3(x, y, z));

				// Top left
				x = (float) (col * tileSize);
				z = (float) (rowEdge - (row + 1) * tileSize);
				y = (float) (heightMap.findHeightAt(x, z));
				vertices.push_back(Vec3(x, y, z));

				// Top right
				x = (float) ((col + 1) * tileSize);
				z = (float) (rowEdge - (row + 1) * tileSize);
				y = (float) (heightMap.findHeightAt(x, z));
				vertices.push_back(Vec3(x, y, z));

				//calculate 4 normals
				x = 0;
				y = 1; // TODO: Use neighbouring vertices to set this
				z = 0;

				// Bottom left
				normals.push_back(Vec3(x, y, z));

				//bot right
				normals.push_back(Vec3(x, y, z));

				//top left
				normals.push_back(Vec3(x, y, z));

				//top right
				normals.push_back(Vec3(x, y, z));

				//calculate 4 texture coords

				//bot left
				u = col / fCols;
				v = row / fRows;
				textureUvs.push_back(Vec2(u, v));

				//bot right
				u = (col + 1) / fCols;
				v = row / fRows;
				textureUvs.push_back(Vec2(u, v));

				//top left
				u = col / fCols;
				v = (row + 1) / fRows;
				textureUvs.push_back(Vec2(u, v));

				//top right
				u = (col + 1) / fCols;
				v = (row + 1) / fRows;
				textureUvs.push_back(Vec2(u, v));

				//calculate indices
				int indexOffset = col * 6 + row * 6 * columnCount;

				//bot left triangle
				indices.push_back(tileOffset + 2);
				indices.push_back(tileOffset);
				indices.push_back(tileOffset + 1);

				//top right triangle
				indices.push_back(tileOffset + 1);
				indices.push_back(tileOffset + 3);
				indices.push_back(tileOffset + 2);
			}
		}

		return TerrainModel(GeometryModel(vertices, textureUvs, normals, indices), heightMap, tileSize, rowCount, columnCount);
	}
}
