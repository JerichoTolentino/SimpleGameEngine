#include "TerrainModel.h"
#include "../Math/Vec3.h"
#include "../Math/Vec2.h"

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
				unsigned int topLeft = row * cols + col;
				unsigned int topRight = topLeft + 1;
				unsigned int bottomLeft = (row + 1) * cols + col;
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

	/*
	// TODO: Test that this actually works (kinda blindly refactored)
	TerrainModel TerrainModel::GenerateTerrainModel(int tileSize, const std::shared_ptr<HeightMap> heightMap)
	{
		int rowCount = heightMap->getWidth() - 1;
		int columnCount = heightMap->getHeight() - 1;
		float fRows = rowCount;
		float fCols = columnCount;
		float rowEdge = (float) (rowCount * tileSize);	// Used when calculating z-coordinate for winding (since -z is forwards)

		auto vertices = std::make_shared<std::vector<Vec3>>(rowCount * columnCount * 4);
		auto normals = std::make_shared<std::vector<Vec3>>(rowCount * columnCount * 4); // TODO: These normals are all set to point Y-up for now
		auto textureUvs = std::make_shared<std::vector<Vec2>>(rowCount * columnCount * 4);
		auto indices = std::make_shared<std::vector<unsigned int>>(rowCount * columnCount * 6);

		for (int row = 0; row < rowCount; row++)
		{
			for (int col = 0; col < columnCount; col++)
			{
				int tileOffset = col * 4 + row * 4 * columnCount;

				// Calculates 4 vertices
				Vec3 vertex;

				// Bottom left
				vertex.x = (float) (col * tileSize);
				vertex.z = (float) (rowEdge - row * tileSize);
				vertex.y = (float)(heightMap->findHeightAt(vertex.x, vertex.z));
				vertices->push_back(vertex);

				// Bottom right
				vertex.x = (float) ((col + 1) * tileSize);
				vertex.z = (float) (rowEdge - row * tileSize);
				vertex.y = (float)(heightMap->findHeightAt(vertex.x, vertex.z));
				vertices->push_back(vertex);

				// Top left
				vertex.x = (float) (col * tileSize);
				vertex.z = (float) (rowEdge - (row + 1) * tileSize);
				vertex.y = (float)(heightMap->findHeightAt(vertex.x, vertex.z));
				vertices->push_back(vertex);

				// Top right
				vertex.x = (float)((col + 1) * tileSize);
				vertex.z = (float) (rowEdge - (row + 1) * tileSize);
				vertex.y = (float)(heightMap->findHeightAt(vertex.x, vertex.z));
				vertices->push_back(vertex);

				//calculate 4 normals
				vertex.x = 0;
				vertex.y = 1; // TODO: Use neighbouring vertices to set this
				vertex.z = 0;

				// Bottom left
				vertices->push_back(vertex);

				//bot right
				vertices->push_back(vertex);

				//top left
				vertices->push_back(vertex);

				//top right
				vertices->push_back(vertex);

				//calculate 4 texture coords
				Vec2 textureCoordinate;

				//bot left
				textureCoordinate.x = col / fCols;
				textureCoordinate.y = row / fRows;
				textureUvs->push_back(textureCoordinate);

				//bot right
				textureCoordinate.x = (col + 1) / fCols;
				textureCoordinate.y = row / fRows;
				textureUvs->push_back(textureCoordinate);

				//top left
				textureCoordinate.x = col / fCols;
				textureCoordinate.y = (row + 1) / fRows;
				textureUvs->push_back(textureCoordinate);

				//top right
				textureCoordinate.x = (col + 1) / fCols;
				textureCoordinate.y = (row + 1) / fRows;
				textureUvs->push_back(textureCoordinate);

				//calculate indices
				int indexOffset = col * 6 + row * 6 * columnCount;

				//bot left triangle
				indices->push_back(tileOffset + 2);
				indices->push_back(tileOffset);
				indices->push_back(tileOffset + 1);

				//top right triangle
				indices->push_back(tileOffset + 1);
				indices->push_back(tileOffset + 3);
				indices->push_back(tileOffset + 2);
			}
		}

		return TerrainModel(std::make_shared<GeometryModel>(GeometryModel(vertices, textureUvs, normals, indices)), heightMap, tileSize, rowCount, columnCount);
	}
	*/
}
