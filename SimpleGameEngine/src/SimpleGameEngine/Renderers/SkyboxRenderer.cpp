#include "SkyboxRenderer.h"
#include "../Loaders/ShaderLoader.h"
#include "../Shaders/SkyboxShaderConstants.h"

using namespace SimpleGameEngine::Loaders;
using namespace SimpleGameEngine::Shaders;

namespace SimpleGameEngine::Renderers
{
	SkyboxRenderer::SkyboxRenderer()
	{
	}

	SkyboxRenderer::SkyboxRenderer(const std::shared_ptr<Shaders::Shader> shader)
	{
		m_shader = shader;
	}

	SkyboxRenderer::SkyboxRenderer(const SkyboxRenderer & other)
		: SkyboxRenderer(other.m_shader)
	{
	}


	SkyboxRenderer::~SkyboxRenderer()
	{
	}



	void SkyboxRenderer::loadSkybox(const Models::SkyboxRenderModel & skybox) const
	{
		glBindVertexArray(skybox.getSkyboxVaoId());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(2);

		ShaderLoader::startShader(*m_shader);

		// Load skybox texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.getTextureId());
		ShaderLoader::loadUniform1i(*m_shader, SkyboxShaderConstants::FRAG_CUBEMAP_SAMPLER, 0);

		ShaderLoader::stopShader(*m_shader);
	}

	void SkyboxRenderer::render(const Models::SkyboxRenderModel & skybox) const
	{
		glDisable(GL_CULL_FACE);

		ShaderLoader::startShader(*m_shader);
		glDrawElements(GL_TRIANGLES, (GLsizei) skybox.getSkyboxModel()->getIndices()->size(), GL_UNSIGNED_INT, 0);
		ShaderLoader::stopShader(*m_shader);

		glEnable(GL_CULL_FACE);
	}

	void SkyboxRenderer::unloadSkybox() const
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glBindVertexArray(0);
	}

	void SkyboxRenderer::loadProjectionMatrix(const Math::Mat4 & proj) const
	{
		ShaderLoader::startShader(*m_shader);
		ShaderLoader::loadUniformMat4f(*m_shader, SkyboxShaderConstants::VERT_PROJECTION_MATRIX, proj);
		ShaderLoader::stopShader(*m_shader);
	}

	void SkyboxRenderer::loadCamera(const Cameras::Camera & camera) const
	{
		ShaderLoader::startShader(*m_shader);
		ShaderLoader::loadUniformMat4f(*m_shader, SkyboxShaderConstants::VERT_VIEW_MATRIX, camera.generateSkyboxViewMatrix());
		ShaderLoader::stopShader(*m_shader);
	}



	SkyboxRenderer & SkyboxRenderer::operator=(const SkyboxRenderer & other)
	{
		m_shader = other.m_shader;

		return *this;
	}
}
