#include "GeometryModel.h"

using namespace SimpleGameEngine::Math;

namespace SimpleGameEngine::Models
{
	GeometryModel::GeometryModel()
	{
	}

	GeometryModel::GeometryModel(const GeometryModel & other)
		: GeometryModel(other.m_vertices, other.m_textureUvs, other.m_normals, other.m_indices)
	{
	}
	
	GeometryModel::GeometryModel(std::vector<Vec3> vertices, std::vector<Vec2> textureUvs, std::vector<Vec3> normals, std::vector<unsigned int> indices)
	{
		m_vertices = vertices;
		m_textureUvs = textureUvs;
		m_normals = normals;
		m_indices = indices;
	}
	
	GeometryModel::~GeometryModel()
	{
	}



	std::vector<Vec3> GeometryModel::getVertices() const
	{
		return m_vertices;
	}

	std::vector<Vec2> GeometryModel::getTextureUvs() const
	{
		return m_textureUvs;
	}

	std::vector<Vec3> GeometryModel::getNormals() const
	{
		return m_normals;
	}
	
	std::vector<unsigned int> GeometryModel::getIndices() const
	{
		return m_indices;
	}



	GeometryModel & GeometryModel::operator=(const GeometryModel & other)
	{
		m_vertices = other.m_vertices;
		m_textureUvs = other.m_textureUvs;
		m_normals = other.m_normals;
		m_indices = other.m_indices;

		return *this;
	}
}
