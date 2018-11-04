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
		Material m_material;



	public:
		RenderModel();
		RenderModel(GeometryModel geometryModel, Material material);
		RenderModel(const RenderModel & other);
		virtual ~RenderModel();



		GeometryModel getGeometryModel() const;
		Material getMaterial() const;



		RenderModel & operator=(const RenderModel & other);
	};
}
