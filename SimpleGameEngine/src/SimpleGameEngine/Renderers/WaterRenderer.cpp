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

	WaterRenderer::WaterRenderer(const std::shared_ptr<Shaders::Shader> shader)
		: m_shader(shader)
	{
		m_dudvMapTextureId = -1;
		m_waterFlowFactor = 0;
		m_waterFlowSpeed = 0.0003f;
	}

	WaterRenderer::WaterRenderer(const WaterRenderer & other)
		: WaterRenderer(other.m_shader)
	{
	}

	WaterRenderer::~WaterRenderer()
	{
	}


	
	void WaterRenderer::loadWaterFlowSpeed(float speed)
	{
		m_waterFlowSpeed = speed;
	}

	void WaterRenderer::loadWaterFlowFactor(float factor)
	{
		m_waterFlowFactor = factor;
	}

	void WaterRenderer::loadWaterDuDvMap(unsigned int dudvMapTextureId)
	{
		ShaderLoader::startShader(*m_shader);

		m_dudvMapTextureId = dudvMapTextureId;

		// Connect texture unit
		ShaderLoader::loadUniform1i(*m_shader, WaterShaderConstants::FRAG_WATER_DUDV_MAP_SAMPLER, 2);

		ShaderLoader::stopShader(*m_shader);
	}

	void WaterRenderer::loadWaterReflectionFbo(const std::shared_ptr<OpenGL::WaterReflectionFbo> waterReflectionFbo)
	{
		ShaderLoader::startShader(*m_shader);

		m_waterReflectionFbo = waterReflectionFbo;

		// Connect texture unit
		ShaderLoader::loadUniform1i(*m_shader, WaterShaderConstants::FRAG_WATER_REFLECTION_SAMPLER, 0);

		ShaderLoader::stopShader(*m_shader);
	}

	void WaterRenderer::loadWaterRefractionFbo(const std::shared_ptr<OpenGL::WaterRefractionFbo> waterRefractionFbo)
	{
		ShaderLoader::startShader(*m_shader);

		m_waterRefractionFbo = waterRefractionFbo;

		// Connect texture unit
		ShaderLoader::loadUniform1i(*m_shader, WaterShaderConstants::FRAG_WATER_REFRACTION_SAMPLER, 1);

		ShaderLoader::stopShader(*m_shader);
	}

	void WaterRenderer::loadCamera(const Cameras::Camera & camera) const
	{
		ShaderLoader::startShader(*m_shader);
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

		// Bind water FBOs
		if (m_waterReflectionFbo != nullptr)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, m_waterReflectionFbo->getTextureId());
		}
		if (m_waterRefractionFbo != nullptr)
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, m_waterRefractionFbo->getTextureId());
		}
		if (m_dudvMapTextureId != -1)
		{
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, m_dudvMapTextureId);
		}
	}
	
	void WaterRenderer::loadWaterEntity(const Models::WaterEntity & entity) const
	{
		ShaderLoader::startShader(*m_shader);

		auto spaceModel = entity.getSpaceModel();
		Mat4 entityTransform;
		entityTransform.setIdentity();
		entityTransform.transform(spaceModel->getPosition(), spaceModel->getRotation(), spaceModel->getScale());
		ShaderLoader::loadUniformMat4f(*m_shader, WaterShaderConstants::VERT_MODEL_MATRIX, entityTransform);
		
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
	
	void WaterRenderer::updateWaterFlow()
	{
		m_waterFlowFactor += m_waterFlowSpeed;
		m_waterFlowFactor = std::fmodf(m_waterFlowFactor, 1);
		ShaderLoader::startShader(*m_shader);
		ShaderLoader::loadUniform1f(*m_shader, WaterShaderConstants::FRAG_WATER_FLOW_FACTOR, m_waterFlowFactor);
		ShaderLoader::stopShader(*m_shader);
	}
	
	
	WaterRenderer & WaterRenderer::operator=(const WaterRenderer & other)
	{
		m_shader = other.m_shader;

		return *this;
	}
}