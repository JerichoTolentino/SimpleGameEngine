#include "sgepch.h"
#include "WaterModel.h"

namespace SimpleGameEngine::Models
{

	WaterModel::WaterModel()
	{
	}

	WaterModel::WaterModel(const WaterModel & other)
		: WaterModel(other.m_vertices, other.m_indices)
	{
	}

	WaterModel::WaterModel(
		const std::shared_ptr<std::vector<float>> vertices,
		const std::shared_ptr<std::vector<unsigned int>> indices)
		: m_vertices(vertices), m_indices(indices)
	{
	}

	WaterModel::~WaterModel()
	{
	}



	std::shared_ptr<std::vector<float>> WaterModel::getVertices() const
	{
		return m_vertices;
	}

	std::shared_ptr<std::vector<unsigned int>> WaterModel::getIndices() const
	{
		return m_indices;
	}



	WaterModel & WaterModel::operator=(const WaterModel & other)
	{
		m_vertices = other.m_vertices;
		m_indices = other.m_indices;

		return *this;
	}
	
	
	
	WaterModel WaterModel::GenerateWaterModel()
	{
		static const float verticesArr[] =
		{
			-1, -1,
			-1,	 1,
			 1,	-1,
			 1,	 1
		};
		auto vertices = std::make_shared<std::vector<float>>(verticesArr, verticesArr + sizeof(verticesArr) / sizeof(verticesArr[0]));

		static const unsigned int indicesArr[] =
		{
			0, 1, 2,
			2, 1, 3
		};
		auto indices = std::make_shared<std::vector<unsigned int>>(indicesArr, indicesArr + sizeof(indicesArr) / sizeof(indicesArr[0]));

		return WaterModel(vertices, indices);
	}
}
