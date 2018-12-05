#include "sgepch.h"
#include "GuiGeometry.h"

namespace SimpleGameEngine::Models
{
	GuiGeometry::GuiGeometry()
	{
	}

	GuiGeometry::GuiGeometry(const GuiGeometry & other)
		: GuiGeometry(other.m_vertices, other.m_textureUvs, other.m_indices)
	{
	}

	GuiGeometry::GuiGeometry(
		const std::shared_ptr<std::vector<float>> vertices, 
		const std::shared_ptr<std::vector<float>> textureUvs, 
		const std::shared_ptr<std::vector<unsigned int>> indices)
	{
		m_vertices = vertices;
		m_textureUvs = textureUvs;
		m_indices = indices;
	}

	GuiGeometry::~GuiGeometry()
	{
	}



	std::shared_ptr<std::vector<float>> GuiGeometry::getVertices() const
	{
		return m_vertices;
	}

	std::shared_ptr<std::vector<float>> GuiGeometry::getTextureUvs() const
	{
		return m_textureUvs;
	}

	std::shared_ptr<std::vector<unsigned int>> GuiGeometry::getIndices() const
	{
		return m_indices;
	}



	GuiGeometry & GuiGeometry::operator=(const GuiGeometry & other)
	{
		m_vertices = other.m_vertices;
		m_textureUvs = other.m_textureUvs;
		m_indices = other.m_indices;

		return *this;
	}



	GuiGeometry GuiGeometry::GenerateQuad()
	{
		static const float verticesArr[] =
		{
			-1,  1,
			-1,	-1,
			 1,	 1,
			 1,	-1
		};
		auto vertices = std::make_shared<std::vector<float>>(verticesArr, verticesArr + sizeof(verticesArr) / sizeof(verticesArr[0]));

		static const float textureUvsArr[] =
		{
			0, 0,
			0, 1,
			1, 0,
			1, 1
		};
		auto textureUvs = std::make_shared<std::vector<float>>(textureUvsArr, textureUvsArr + sizeof(textureUvsArr) / sizeof(textureUvsArr[0]));

		static const unsigned int indicesArr[] =
		{
			0, 1, 2,
			2, 1, 3
		};
		auto indices = std::make_shared<std::vector<unsigned int>>(indicesArr, indicesArr + sizeof(indicesArr) / sizeof(indicesArr[0]));

		return GuiGeometry(vertices, textureUvs, indices);
	}
}
