#include "RenderModel.h"

namespace SimpleGameEngine::Models
{
	RenderModel::RenderModel()
	{
	}

	RenderModel::RenderModel(GeometryModel geometryModel, SpaceModel spaceModel, Material material)
	{
		m_geomtryModel = geometryModel;
		m_spaceModel = spaceModel;
		m_material = material;
	}

	RenderModel::RenderModel(const RenderModel & other)
		: RenderModel(other.m_geomtryModel, other.m_spaceModel, other.m_material)
	{
	}


	RenderModel::~RenderModel()
	{
	}



	GeometryModel RenderModel::getGeometryModel() const
	{
		return m_geomtryModel;
	}

	SpaceModel RenderModel::getSpaceModel() const
	{
		return m_spaceModel;
	}

	Material RenderModel::getMaterial() const
	{
		return m_material;
	}



	RenderModel & RenderModel::operator=(const RenderModel & other)
	{
		m_geomtryModel = other.m_geomtryModel;
		m_spaceModel = other.m_spaceModel;
		m_material = other.m_material;

		return *this;
	}
}
