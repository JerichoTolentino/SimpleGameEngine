#pragma once
#include <GL/glew.h>
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
		GLuint m_textureId;
		GLuint m_geometryVaoId;



	public:
		RenderModel();
		RenderModel(GeometryModel geometryModel, Material material, GLuint geometryVaoId, GLuint textureId);
		RenderModel(const RenderModel & other);
		virtual ~RenderModel();



		GeometryModel getGeometryModel() const;
		Material getMaterial() const;
		GLuint getGeometryVaoId() const;
		GLuint getTextureId() const;



		RenderModel & operator=(const RenderModel & other);
	};
}
