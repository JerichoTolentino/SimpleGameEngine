#include "sgepch.h"
#include "WaterRenderer.h"

#include "../Loaders/ShaderLoader.h"
#include "../Shaders/WaterShaderConstants.h"

using namespace SimpleGameEngine::Loaders;
using namespace SimpleGameEngine::Shaders;
using namespace SimpleGameEngine::Math;

namespace SimpleGameEngine::Renderers
{

	WaterRenderer::WaterRenderer()
	{
	}

	WaterRenderer::WaterRenderer(const std::shared_ptr<Shaders::Shader> shader,
								 unsigned int reflectionTextureId,
								 unsigned int refractionTextureId,
								 unsigned int depthTextureId)
		: m_shader(shader), m_reflectionTextureId(reflectionTextureId), m_refractionTextureId(refractionTextureId), m_depthTextureId(depthTextureId)
	{
		// TODO: REFACTOR THIS
		//
		// Connect texture units
		ShaderLoader::startShader(*m_shader);
		ShaderLoader::loadUniform1i(*m_shader, WaterShaderConstants::FRAG_WATER_REFLECTION_SAMPLER, 0);
		ShaderLoader::loadUniform1i(*m_shader, WaterShaderConstants::FRAG_WATER_REFRACTION_SAMPLER, 1);
		ShaderLoader::loadUniform1i(*m_shader, WaterShaderConstants::FRAG_WATER_DUDV_MAP_SAMPLER, 2);
		ShaderLoader::loadUniform1i(*m_shader, WaterShaderConstants::FRAG_WATER_NORMAL_MAP_SAMPLER, 3);
		ShaderLoader::loadUniform1i(*m_shader, WaterShaderConstants::FRAG_DEPTH_MAP_SAMPLER, 4);
		ShaderLoader::stopShader(*m_shader);
	}

	WaterRenderer::WaterRenderer(const WaterRenderer & other)
		: WaterRenderer(other.m_shader, 
						other.m_reflectionTextureId,
						other.m_refractionTextureId,
						other.m_depthTextureId)
	{
	}

	WaterRenderer::~WaterRenderer()
	{
	}



	void WaterRenderer::loadClippingPlanes(float nearPlane, float farPlane) const
	{
		ShaderLoader::startShader(*m_shader);
		ShaderLoader::loadUniform1f(*m_shader, WaterShaderConstants::FRAG_NEAR_CLIPPING_PLANE, nearPlane);
		ShaderLoader::loadUniform1f(*m_shader, WaterShaderConstants::FRAG_FAR_CLIPPING_PLANE, farPlane);
		ShaderLoader::stopShader(*m_shader);
	}

	void WaterRenderer::loadSun(const Models::LightSource & light) const
	{
		ShaderLoader::startShader(*m_shader);

		ShaderLoader::loadUniformVec3f(*m_shader, WaterShaderConstants::VERT_SUN_POSITION, light.getPosition());
		ShaderLoader::loadUniformVec3f(*m_shader, WaterShaderConstants::FRAG_SUN_COLOR, light.getColor());

		ShaderLoader::stopShader(*m_shader);
	}

	void WaterRenderer::loadCamera(const Cameras::Camera & camera) const
	{
		ShaderLoader::startShader(*m_shader);
		ShaderLoader::loadUniformVec3f(*m_shader, WaterShaderConstants::VERT_EYE_POSITION, camera.getPosition());
		ShaderLoader::loadUniformMat4f(*m_shader, WaterShaderConstants::VERT_VIEW_MATRIX, camera.generateViewMatrix());
		ShaderLoader::stopShader(*m_shader);
	}
	
	void WaterRenderer::loadLights(const std::vector<std::shared_ptr<Models::LightSource>>& lights) const
	{
		// TODO: Fill in
	}
	
	void WaterRenderer::loadProjectionMatrix(const Math::Mat4 & proj) const
	{
		ShaderLoader::startShader(*m_shader);
		ShaderLoader::loadUniformMat4f(*m_shader, WaterShaderConstants::VERT_PROJECTION_MATRIX, proj);
		ShaderLoader::stopShader(*m_shader);
	}
	
	void WaterRenderer::loadWaterRenderModel(const Models::WaterRenderModel & waterRenderModel) const
	{
		// Bind the VAO
		glBindVertexArray(waterRenderModel.getVaoId());
		glEnableVertexAttribArray(0);

		// Bind reflection texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_reflectionTextureId);
		
		// Bind refraction texture
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, m_refractionTextureId);
		
		// Bind DuDv texture map
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, waterRenderModel.getDuDvMapTextureId());

		// Bind normal texture map
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, waterRenderModel.getNormalMapTextureId());

		// Bind depth texture map
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, m_depthTextureId);
		
	}
	
	void WaterRenderer::loadWaterEntity(const Models::WaterEntity & entity) const
	{
		ShaderLoader::startShader(*m_shader);

		auto spaceModel = entity.getSpaceModel();
		Mat4 entityTransform;
		entityTransform.setIdentity();
		entityTransform.transform(spaceModel->getPosition(), spaceModel->getRotation(), spaceModel->getScale());
		ShaderLoader::loadUniformMat4f(*m_shader, WaterShaderConstants::VERT_MODEL_MATRIX, entityTransform);

		// Load in properties
		auto properties = *entity.getWaterProperties();
		ShaderLoader::loadUniform1f(*m_shader, WaterShaderConstants::FRAG_WATER_FLOW_FACTOR, entity.getFlowFactor());
		ShaderLoader::loadUniform1f(*m_shader, WaterShaderConstants::FRAG_FRESNEL_CONSTANT, properties.getFresnelConstant());
		ShaderLoader::loadUniform1f(*m_shader, WaterShaderConstants::FRAG_REFLECTIVITY, properties.getReflectivity());
		ShaderLoader::loadUniform1f(*m_shader, WaterShaderConstants::FRAG_SHINE_DAMPER, properties.getShineDamper());
		ShaderLoader::loadUniform1f(*m_shader, WaterShaderConstants::VERT_TILE_FACTOR, properties.getTileFactor());
		ShaderLoader::loadUniform1f(*m_shader, WaterShaderConstants::FRAG_WAVE_STRENGTH, properties.getWaveStrength());
		
		ShaderLoader::stopShader(*m_shader);
	}
	
	void WaterRenderer::render(const Models::WaterEntity & entity) const
	{
		ShaderLoader::startShader(*m_shader);
		glDrawElements(GL_TRIANGLES, (GLsizei) entity.getWaterRenderModel()->getWaterModel()->getIndices()->size(), GL_UNSIGNED_INT, 0);
		ShaderLoader::stopShader(*m_shader);
	}
	
	void WaterRenderer::unloadWaterRenderModel() const
	{
		glBindVertexArray(0);
	}
	
	
	WaterRenderer & WaterRenderer::operator=(const WaterRenderer & other)
	{
		m_shader = other.m_shader;
		m_reflectionTextureId = other.m_reflectionTextureId;
		m_refractionTextureId = other.m_refractionTextureId;
		m_depthTextureId = other.m_depthTextureId;

		return *this;
	}
}
