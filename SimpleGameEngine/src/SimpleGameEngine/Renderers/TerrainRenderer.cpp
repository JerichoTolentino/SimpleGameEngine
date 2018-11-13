#include "TerrainRenderer.h"
#include "../Loaders/ShaderLoader.h"
#include "../Shaders/TerrainShaderConstants.h"

using namespace SimpleGameEngine::Models;
using namespace SimpleGameEngine::Math;
using namespace SimpleGameEngine::Cameras;
using namespace SimpleGameEngine::Loaders;
using namespace SimpleGameEngine::Shaders;

namespace SimpleGameEngine::Renderers
{
	TerrainRenderer::TerrainRenderer()
	{
	}

	TerrainRenderer::TerrainRenderer(Shaders::Shader shader)
	{
		m_shader = shader;
	}

	TerrainRenderer::TerrainRenderer(const TerrainRenderer & other)
		: TerrainRenderer(other.m_shader)
	{
	}

	TerrainRenderer::~TerrainRenderer()
	{
	}



	void TerrainRenderer::loadTerrain(Models::TerrainRenderModel terrain) const
	{
		TerrainModel model = terrain.getTerrainModel();

		// Bind terrain VAO
		glBindVertexArray(terrain.getGeometryVaoId());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		ShaderLoader::startShader(m_shader);

		// Bind texture pack
		TexturePack texturePack = terrain.getTexturePack();

		// Blend map
		glActiveTexture(TerrainShaderConstants::BLEND_MAP_TEXTURE_SLOT_OPENGL);
		glBindTexture(GL_TEXTURE_2D, texturePack.getBlendMapTextureId());

		// Red texture
		glActiveTexture(TerrainShaderConstants::RED_TEXTURE_SLOT_OPENGL);
		glBindTexture(GL_TEXTURE_2D, texturePack.getRedTextureId());

		// Green texture
		glActiveTexture(TerrainShaderConstants::GREEN_TEXTURE_SLOT_OPENGL);
		glBindTexture(GL_TEXTURE_2D, texturePack.getGreenTextureId());

		// Blue texture
		glActiveTexture(TerrainShaderConstants::BLUE_TEXTURE_SLOT_OPENGL);
		glBindTexture(GL_TEXTURE_2D, texturePack.getBlueTextureId());

		// Background texture
		glActiveTexture(TerrainShaderConstants::BACKGROUND_TEXTURE_SLOT_OPENGL);
		glBindTexture(GL_TEXTURE_2D, texturePack.getBackgroundTextureId());


		// Load texture pack uniforms
		ShaderLoader::loadUniform1f(m_shader, TerrainShaderConstants::FRAG_BLEND_SAMPLER, TerrainShaderConstants::BLEND_MAP_TEXTURE_SLOT);
		ShaderLoader::loadUniform1f(m_shader, TerrainShaderConstants::FRAG_RED_SAMPLER, TerrainShaderConstants::RED_TEXTURE_SLOT);
		ShaderLoader::loadUniform1f(m_shader, TerrainShaderConstants::FRAG_GREEN_SAMPLER, TerrainShaderConstants::GREEN_TEXTURE_SLOT);
		ShaderLoader::loadUniform1f(m_shader, TerrainShaderConstants::FRAG_BLUE_SAMPLER, TerrainShaderConstants::BLUE_TEXTURE_SLOT);
		ShaderLoader::loadUniform1f(m_shader, TerrainShaderConstants::FRAG_BACKGROUND_SAMPLER, TerrainShaderConstants::BACKGROUND_TEXTURE_SLOT);

		// Load shading uniforms
		LightingModel lightingModel = terrain.getMaterial().getLightingModel();
		ShaderLoader::loadUniform1f(m_shader, TerrainShaderConstants::FRAG_AMBIENT, lightingModel.getAmbient());
		ShaderLoader::loadUniform1f(m_shader, TerrainShaderConstants::FRAG_DIFFUSE, lightingModel.getDiffuse());
		ShaderLoader::loadUniform1f(m_shader, TerrainShaderConstants::FRAG_OPACITY, lightingModel.getOpacity());

		ShaderLoader::stopShader(m_shader);
	}

	void TerrainRenderer::render(Models::TerrainRenderModel terrain) const
	{
		ShaderLoader::startShader(m_shader);
		glDrawElements(GL_TRIANGLES, terrain.getTerrainModel().getGeometryModel().getIndices().size(), GL_UNSIGNED_INT, 0);
		ShaderLoader::stopShader(m_shader);
	}

	void TerrainRenderer::unloadTerrain() const
	{
		// Unload texture pack
		glActiveTexture(TerrainShaderConstants::BLEND_MAP_TEXTURE_SLOT_OPENGL);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(TerrainShaderConstants::RED_TEXTURE_SLOT_OPENGL);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(TerrainShaderConstants::GREEN_TEXTURE_SLOT_OPENGL);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(TerrainShaderConstants::BLUE_TEXTURE_SLOT_OPENGL);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(TerrainShaderConstants::BACKGROUND_TEXTURE_SLOT_OPENGL);
		glBindTexture(GL_TEXTURE_2D, 0);

		// Unload terrain VAO
		glBindVertexArray(0);
	}

	void TerrainRenderer::loadProjectionMatrix(Math::Mat4 proj) const
	{
		ShaderLoader::startShader(m_shader);
		ShaderLoader::loadUniformMat4f(m_shader, TerrainShaderConstants::VERT_PROJECTION_MATRIX, proj);
		ShaderLoader::stopShader(m_shader);
	}

	void TerrainRenderer::loadCamera(const std::shared_ptr<Cameras::Camera> camera) const
	{
		ShaderLoader::startShader(m_shader);
		ShaderLoader::loadUniformMat4f(m_shader, TerrainShaderConstants::VERT_VIEW_MATRIX, camera->generateViewMatrix());
		ShaderLoader::stopShader(m_shader);
	}

	void TerrainRenderer::loadLight(Math::Vec3 light) const
	{
		ShaderLoader::startShader(m_shader);
		ShaderLoader::loadUniformVec3f(m_shader, TerrainShaderConstants::VERT_LIGHT_POSITION, light);
		ShaderLoader::stopShader(m_shader);
	}



	TerrainRenderer & TerrainRenderer::operator=(const TerrainRenderer & other)
	{
		m_shader = other.m_shader;

		return *this;
	}
}