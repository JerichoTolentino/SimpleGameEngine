#include "sgepch.h"
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

	TerrainRenderer::TerrainRenderer(const std::shared_ptr<Shaders::Shader> shader)
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



	void TerrainRenderer::loadTerrain(const Models::TerrainRenderModel & terrain) const
	{
		// Bind terrain VAO
		glBindVertexArray(terrain.getGeometryVaoId());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		ShaderLoader::startShader(*m_shader);

		// Load in model matrix
		SpaceModel spaceModel = *(terrain.getSpaceModel());
		Mat4 modelMatrix;
		modelMatrix.setIdentity();
		modelMatrix.transform(spaceModel.getPosition(), spaceModel.getRotation(), spaceModel.getScale());
		ShaderLoader::loadUniformMat4f(*m_shader, TerrainShaderConstants::VERT_MODEL_MATRIX, modelMatrix);

		// Load in tile factor
		ShaderLoader::loadUniform1f(*m_shader, TerrainShaderConstants::FRAG_TILE_FACTOR, terrain.getTerrainModel()->getTileFactor());

		// Load in texture pack
		auto texturePack = terrain.getTexturePack();

		// Blend map
		glActiveTexture(TerrainShaderConstants::BLEND_MAP_TEXTURE_SLOT_OPENGL);
		glBindTexture(GL_TEXTURE_2D, texturePack->getBlendMapTextureId());
		ShaderLoader::loadUniform1i(*m_shader, TerrainShaderConstants::FRAG_BLEND_SAMPLER, TerrainShaderConstants::BLEND_MAP_TEXTURE_SLOT);

		// Red texture
		glActiveTexture(TerrainShaderConstants::RED_TEXTURE_SLOT_OPENGL);
		glBindTexture(GL_TEXTURE_2D, texturePack->getRedTextureId());
		ShaderLoader::loadUniform1i(*m_shader, TerrainShaderConstants::FRAG_RED_SAMPLER, TerrainShaderConstants::RED_TEXTURE_SLOT);

		// Green texture
		glActiveTexture(TerrainShaderConstants::GREEN_TEXTURE_SLOT_OPENGL);
		glBindTexture(GL_TEXTURE_2D, texturePack->getGreenTextureId());
		ShaderLoader::loadUniform1i(*m_shader, TerrainShaderConstants::FRAG_GREEN_SAMPLER, TerrainShaderConstants::GREEN_TEXTURE_SLOT);

		// Blue texture
		glActiveTexture(TerrainShaderConstants::BLUE_TEXTURE_SLOT_OPENGL);
		glBindTexture(GL_TEXTURE_2D, texturePack->getBlueTextureId());
		ShaderLoader::loadUniform1i(*m_shader, TerrainShaderConstants::FRAG_BLUE_SAMPLER, TerrainShaderConstants::BLUE_TEXTURE_SLOT);

		// Background texture
		glActiveTexture(TerrainShaderConstants::BACKGROUND_TEXTURE_SLOT_OPENGL);
		glBindTexture(GL_TEXTURE_2D, texturePack->getBackgroundTextureId());
		ShaderLoader::loadUniform1i(*m_shader, TerrainShaderConstants::FRAG_BACKGROUND_SAMPLER, TerrainShaderConstants::BACKGROUND_TEXTURE_SLOT);

		// Load shading uniforms
		auto lightingModel = terrain.getMaterial()->getLightingModel();
		ShaderLoader::loadUniform1f(*m_shader, TerrainShaderConstants::FRAG_AMBIENT, lightingModel->getAmbient());
		ShaderLoader::loadUniform1f(*m_shader, TerrainShaderConstants::FRAG_DIFFUSE, lightingModel->getDiffuse());
		ShaderLoader::loadUniform1f(*m_shader, TerrainShaderConstants::FRAG_OPACITY, lightingModel->getOpacity());

		ShaderLoader::stopShader(*m_shader);
	}

	void TerrainRenderer::render(const Models::TerrainRenderModel & terrain) const
	{
		glDisable(GL_CULL_FACE);

		ShaderLoader::startShader(*m_shader);
		glDrawElements(GL_TRIANGLES, terrain.getTerrainModel()->getGeometryModel()->getIndices()->size(), GL_UNSIGNED_INT, 0);
		ShaderLoader::stopShader(*m_shader);

		glEnable(GL_CULL_FACE);
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

	void TerrainRenderer::loadProjectionMatrix(const Math::Mat4 & proj) const
	{
		ShaderLoader::startShader(*m_shader);
		ShaderLoader::loadUniformMat4f(*m_shader, TerrainShaderConstants::VERT_PROJECTION_MATRIX, proj);
		ShaderLoader::stopShader(*m_shader);
	}

	void TerrainRenderer::loadCamera(const Cameras::Camera & camera) const
	{
		ShaderLoader::startShader(*m_shader);
		ShaderLoader::loadUniformMat4f(*m_shader, TerrainShaderConstants::VERT_VIEW_MATRIX, camera.generateViewMatrix());
		ShaderLoader::stopShader(*m_shader);
	}

	void TerrainRenderer::loadLights(const std::vector<std::shared_ptr<Models::LightSource>> & lights) const
	{
		ShaderLoader::startShader(*m_shader);

		for (int i = 0; i < TerrainShaderConstants::MAX_LIGHTS; i++)
		{
			auto light = i < lights.size() ? *lights.at(i) : LightSource(Vec3(0, 0, 0), Vec3(0, 0, 0));
			ShaderLoader::loadUniformVec3f(
				*m_shader, 
				TerrainShaderConstants::VERT_LIGHT_POSITIONS + "[" + std::to_string(i) + "]", 
				light.getPosition());
			ShaderLoader::loadUniformVec3f(
				*m_shader,
				TerrainShaderConstants::FRAG_LIGHT_COLORS + "[" + std::to_string(i) + "]",
				light.getColor());
			ShaderLoader::loadUniformVec3f(
				*m_shader,
				TerrainShaderConstants::FRAG_LIGHT_ATTENUATIONS + "[" + std::to_string(i) + "]",
				light.getAttenuation());
		}
		
		ShaderLoader::stopShader(*m_shader);
	}



	TerrainRenderer & TerrainRenderer::operator=(const TerrainRenderer & other)
	{
		m_shader = other.m_shader;

		return *this;
	}
}