#include "RenderModel.h"

namespace SimpleGameEngine::Models
{
	RenderModel::RenderModel()
	{
	}

	RenderModel::RenderModel(GeometryModel geometryModel, Material material, GLuint geometryVaoId, GLuint textureId)
	{
		m_geomtryModel = geometryModel;
		m_material = material;
		m_geometryVaoId = geometryVaoId;
		m_textureId = textureId;
	}

	RenderModel::RenderModel(const RenderModel & other)
		: RenderModel(other.m_geomtryModel, other.m_material, other.m_geometryVaoId, other.m_textureId)
	{
	}


	RenderModel::~RenderModel()
	{
	}



	GeometryModel RenderModel::getGeometryModel() const
	{
		return m_geomtryModel;
	}

	Material RenderModel::getMaterial() const
	{
		return m_material;
	}

	GLuint RenderModel::getGeometryVaoId() const
	{
		return m_geometryVaoId;
	}

	GLuint RenderModel::getTextureId() const
	{
		return m_textureId;
	}



	RenderModel & RenderModel::operator=(const RenderModel & other)
	{
		m_geomtryModel = other.m_geomtryModel;
		m_material = other.m_material;
		m_geometryVaoId = other.m_geometryVaoId;
		m_textureId = other.m_textureId;

		return *this;
	}
}
