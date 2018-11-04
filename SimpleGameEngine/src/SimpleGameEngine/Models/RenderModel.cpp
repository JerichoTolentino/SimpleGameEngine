#include "RenderModel.h"

namespace SimpleGameEngine::Models
{
	RenderModel::RenderModel()
	{
	}

	RenderModel::RenderModel(GeometryModel geometryModel, Material material)
	{
		m_geomtryModel = geometryModel;
		m_material = material;
	}

	RenderModel::RenderModel(const RenderModel & other)
		: RenderModel(other.m_geomtryModel, other.m_material)
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



	RenderModel & RenderModel::operator=(const RenderModel & other)
	{
		m_geomtryModel = other.m_geomtryModel;
		m_material = other.m_material;

		return *this;
	}
}
