#include "sgepch.h"
#include "GuiRenderer.h"

#include "../Loaders/ShaderLoader.h"
#include "../Shaders/GuiShaderConstants.h"

using namespace SimpleGameEngine::Math;
using namespace SimpleGameEngine::Loaders;
using namespace SimpleGameEngine::Shaders;

namespace SimpleGameEngine::Renderers
{
	GuiRenderer::GuiRenderer()
	{
	}

	GuiRenderer::GuiRenderer(const GuiRenderer & other)
		: GuiRenderer(other.m_shader)
	{
	}

	GuiRenderer::GuiRenderer(const std::shared_ptr<Shaders::Shader> shader)
	{
		m_shader = shader;
	}

	GuiRenderer::~GuiRenderer()
	{
	}



	void GuiRenderer::loadGuiRenderElement(const Models::GuiRenderElement & guiRenderElement) const
	{
		// Bind the gui render element'sVAO
		glBindVertexArray(guiRenderElement.getVaoId());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		// Bind entity texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, guiRenderElement.getTextureId());
	}

	void GuiRenderer::loadGuiElement(const Models::GuiElement & guiElement) const
	{
		ShaderLoader::startShader(*m_shader);

		// Convert 2D data to 3D data
		Vec3 position(guiElement.getPosition().x, guiElement.getPosition().y, 0);
		Vec3 rotation(0, 0, guiElement.getAngle());
		Vec3 scale(guiElement.getScale().x, guiElement.getScale().y, 1);

		// Load in transformation matrix
		Mat4 elementTransform;
		elementTransform.setIdentity();
		elementTransform.transform(position, rotation, scale);
		ShaderLoader::loadUniformMat4f(*m_shader, GuiShaderConstants::VERT_MODEL_MATRIX, elementTransform);

		// Load in texture sampler location
		ShaderLoader::loadUniform1i(*m_shader, GuiShaderConstants::FRAG_TEXTURE_SAMPLER, 0);

		ShaderLoader::stopShader(*m_shader);
	}
	
	void GuiRenderer::render(const Models::GuiRenderElement & guiRenderElement) const
	{
		ShaderLoader::startShader(*m_shader);
		glDrawElements(GL_TRIANGLES, (GLsizei) Models::GuiElement::INDICES_COUNT, GL_UNSIGNED_INT, 0);
		ShaderLoader::stopShader(*m_shader);
	}
	
	void GuiRenderer::unloadGuiRenderElement() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindVertexArray(0);
	}
	
	
	
	GuiRenderer & GuiRenderer::operator=(const GuiRenderer & other)
	{
		m_shader = other.m_shader;

		return *this;
	}
}
