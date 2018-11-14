#include "RenderModel.h"

namespace SimpleGameEngine::Models
{
	RenderModel::RenderModel()
	{
	}

	RenderModel::RenderModel(
		const std::shared_ptr<GeometryModel> geometryModel, 
		const std::shared_ptr<Material> material, 
		GLuint geometryVaoId, 
		GLuint textureId,
		GLuint reflectionMapTextureId)
	{
		m_geomtryModel = geometryModel;
		m_material = material;
		m_geometryVaoId = geometryVaoId;
		m_textureId = textureId;
		m_reflectionMapTextureId = reflectionMapTextureId;
	}

	RenderModel::RenderModel(const RenderModel & other)
		: RenderModel(other.m_geomtryModel, other.m_material, other.m_geometryVaoId, other.m_textureId, other.m_reflectionMapTextureId)
	{
	}


	RenderModel::~RenderModel()
	{
	}



	std::shared_ptr<GeometryModel> RenderModel::getGeometryModel() const
	{
		return m_geomtryModel;
	}

	std::shared_ptr<Material> RenderModel::getMaterial() const
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

	GLuint RenderModel::getReflectionMapTextureId() const
	{
		return m_reflectionMapTextureId;
	}

	bool RenderModel::hasReflectionMap() const
	{
		return m_reflectionMapTextureId != (unsigned int) -1;
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
