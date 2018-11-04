#pragma once
#include "GeometryModel.h"
#include "SpaceModel.h"
#include "Material.h"

namespace SimpleGameEngine::Models
{
	class RenderModel
	{
	private:
		GeometryModel m_geomtryModel;
		SpaceModel m_spaceModel;
		Material m_material;



	public:
		RenderModel();
		RenderModel(GeometryModel geometryModel, SpaceModel spaceModel, Material material);
		RenderModel(const RenderModel & other);
		virtual ~RenderModel();



		GeometryModel getGeometryModel() const;
		SpaceModel getSpaceModel() const;
		Material getMaterial() const;



		RenderModel & operator=(const RenderModel & other);
	};
}
