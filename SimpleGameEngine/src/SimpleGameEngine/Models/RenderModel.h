#pragma once
#include <memory>
#include <GL/glew.h>
#include "GeometryModel.h"
#include "SpaceModel.h"
#include "Material.h"

namespace SimpleGameEngine::Models
{
	class RenderModel
	{
	private:
		std::shared_ptr<GeometryModel> m_geomtryModel;
		std::shared_ptr<Material> m_material;
		GLuint m_textureId;
		GLuint m_geometryVaoId;
		GLuint m_reflectionMapTextureId;



	public:
		RenderModel();
		RenderModel(
			const std::shared_ptr<GeometryModel> geometryModel, 
			const std::shared_ptr<Material> material, 
			GLuint geometryVaoId, 
			GLuint textureId,
			GLuint reflectionMapTextureId = -1);
		RenderModel(const RenderModel & other);
		virtual ~RenderModel();



		std::shared_ptr<GeometryModel> getGeometryModel() const;
		std::shared_ptr<Material> getMaterial() const;
		GLuint getGeometryVaoId() const;
		GLuint getTextureId() const;
		GLuint getReflectionMapTextureId() const;
		bool hasReflectionMap() const;



		RenderModel & operator=(const RenderModel & other);
	};
}
