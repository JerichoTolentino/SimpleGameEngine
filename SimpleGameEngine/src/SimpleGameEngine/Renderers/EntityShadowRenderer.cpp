#include "sgepch.h"
#include "EntityShadowRenderer.h"

#include "../Loaders/ShaderLoader.h"
#include "../Shaders/ShadowShaderConstants.h"

using namespace SimpleGameEngine::Loaders;
using namespace SimpleGameEngine::Shaders;

namespace SimpleGameEngine::Renderers
{
	EntityShadowRenderer::EntityShadowRenderer()
	{
	}

	EntityShadowRenderer::EntityShadowRenderer(const EntityShadowRenderer & other)
		: EntityShadowRenderer(other.m_shader)
	{
	}

	EntityShadowRenderer::EntityShadowRenderer(const std::shared_ptr<Shaders::Shader> shader)
		: m_shader(shader)
	{
	}

	EntityShadowRenderer::~EntityShadowRenderer()
	{
	}

	void EntityShadowRenderer::loadModelMatrix(const Math::Mat4 & matrix) const
	{
		ShaderLoader::startShader(*m_shader);
		ShaderLoader::loadUniformMat4f(*m_shader, "model_matrix", matrix);
		ShaderLoader::stopShader(*m_shader);
	}

	void EntityShadowRenderer::loadViewMatrix(const Math::Mat4 & matrix) const
	{
		ShaderLoader::startShader(*m_shader);
		ShaderLoader::loadUniformMat4f(*m_shader, "view_matrix", matrix);
		ShaderLoader::stopShader(*m_shader);
	}

	void EntityShadowRenderer::loadProjectionMatrix(const Math::Mat4 & matrix) const
	{
		ShaderLoader::startShader(*m_shader);
		ShaderLoader::loadUniformMat4f(*m_shader, "projection_matrix", matrix);
		ShaderLoader::stopShader(*m_shader);
	}



	void EntityShadowRenderer::loadTextureUnits() const
	{
		ShaderLoader::startShader(*m_shader);
		ShaderLoader::loadUniform1i(*m_shader, ShadowShaderConstants::FRAG_TEXTURE_SAMPLER, 0);
		ShaderLoader::stopShader(*m_shader);
	}

	void EntityShadowRenderer::loadModelViewProjectionMatrix(const Math::Mat4 & modelViewProjectionMatrix) const
	{
		ShaderLoader::startShader(*m_shader);
		ShaderLoader::loadUniformMat4f(*m_shader, ShadowShaderConstants::VERT_MVP_MATRIX, modelViewProjectionMatrix);
		ShaderLoader::stopShader(*m_shader);
	}

	void EntityShadowRenderer::loadRenderModel(const Models::RenderModel & renderModel) const
	{
		// Bind the VAO
		glBindVertexArray(renderModel.getGeometryVaoId());
		glEnableVertexAttribArray(0);
	}
	
	void EntityShadowRenderer::render(const Models::Entity & entity) const
	{
		ShaderLoader::startShader(*m_shader);
		glDrawElements(GL_TRIANGLES, (GLsizei) entity.getRenderModel()->getGeometryModel()->getIndices()->size(), GL_UNSIGNED_INT, 0);
		ShaderLoader::stopShader(*m_shader);
	}
	
	void EntityShadowRenderer::unloadRenderModel() const
	{
		glBindVertexArray(0);
	}
	
	
	
	EntityShadowRenderer & EntityShadowRenderer::operator=(const EntityShadowRenderer & other)
	{
		m_shader = other.m_shader;

		return *this;
	}
}
