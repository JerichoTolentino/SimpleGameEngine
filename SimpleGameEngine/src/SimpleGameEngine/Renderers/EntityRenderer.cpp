#include "EntityRenderer.h"
#include "../Loaders/ShaderLoader.h"
#include "../Shaders/EntityShaderConstants.h"

using namespace SimpleGameEngine::Cameras;
using namespace SimpleGameEngine::Math;
using namespace SimpleGameEngine::Models;
using namespace SimpleGameEngine::Loaders;
using namespace SimpleGameEngine::Shaders;

namespace SimpleGameEngine::Renderers
{
	EntityRenderer::EntityRenderer()
	{
	}

	EntityRenderer::EntityRenderer(const std::shared_ptr<Shader> shader)
	{
		m_shader = shader;
	}

	EntityRenderer::EntityRenderer(const EntityRenderer & other)
		: EntityRenderer(other.m_shader)
	{
	}

	EntityRenderer::~EntityRenderer()
	{
	}



	void EntityRenderer::loadCamera(const Cameras::Camera & camera) const
	{
		ShaderLoader::startShader(*m_shader);
		ShaderLoader::loadUniformVec3f(*m_shader, EntityShaderConstants::VERT_EYE_POSITION, camera.getPosition());
		ShaderLoader::loadUniformMat4f(*m_shader, EntityShaderConstants::VERT_VIEW_MATRIX, camera.generateViewMatrix());
		ShaderLoader::stopShader(*m_shader);
	}

	void EntityRenderer::loadLights(const std::vector<Models::LightSource> & lights) const
	{
		ShaderLoader::startShader(*m_shader);

		// Load in each light's color and position
		for (int i = 0; i < EntityShaderConstants::MAX_LIGHTS; i++)
		{
			auto light = i < lights.size() ? lights.at(i) : LightSource(Vec3(0, 0, 0), Vec3(0, 0, 0));
			ShaderLoader::loadUniformVec3f(
				*m_shader, 
				EntityShaderConstants::VERT_LIGHT_POSITIONS + "[" + std::to_string(i) + "]", 
				light.getPosition());
			ShaderLoader::loadUniformVec3f(
				*m_shader,
				EntityShaderConstants::FRAG_LIGHT_COLORS + "[" + std::to_string(i) + "]",
				light.getColor());
			ShaderLoader::loadUniformVec3f(
				*m_shader,
				EntityShaderConstants::FRAG_LIGHT_ATTENUATIONS + "[" + std::to_string(i) + "]",
				light.getAttenuation());
		}
		
		ShaderLoader::stopShader(*m_shader);
	}

	void EntityRenderer::loadProjectionMatrix(const Math::Mat4 & proj) const
	{
		ShaderLoader::startShader(*m_shader);
		ShaderLoader::loadUniformMat4f(*m_shader, EntityShaderConstants::VERT_PROJECTION_MATRIX, proj);
		ShaderLoader::stopShader(*m_shader);
	}

	void EntityRenderer::loadRenderModel(const Models::RenderModel & renderModel) const
	{
		// Bind the geometry model's VAO
		glBindVertexArray(renderModel.getGeometryVaoId());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// Bind entity texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, renderModel.getTextureId());

		// Bind reflection map
		if (renderModel.hasReflectionMap())
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_CUBE_MAP, renderModel.getReflectionMapTextureId());
		}
	}

	void EntityRenderer::loadEntity(const Models::Entity & entity) const
	{
		auto renderModel = entity.getRenderModel();

		// Startup shader
		ShaderLoader::startShader(*m_shader);

		// Load in the entity's transformation
		auto spaceModel = entity.getSpaceModel();
		Mat4 entityTransform;
		entityTransform.setIdentity();
		entityTransform.transform(spaceModel->getPosition(), spaceModel->getRotation(), spaceModel->getScale());
		ShaderLoader::loadUniformMat4f(*m_shader, EntityShaderConstants::VERT_MODEL_MATRIX, entityTransform);

		// Load in entity texture sampler locations
		ShaderLoader::loadUniform1i(*m_shader, EntityShaderConstants::FRAG_TEXTURE_SAMPLER, 0);
		if (renderModel->hasReflectionMap())
		{
			ShaderLoader::loadUniform1i(*m_shader, EntityShaderConstants::FRAG_CUBEMAP_SAMPLER, 1);
		}

		// Load in the entity's material
		auto lightingModel = renderModel->getMaterial()->getLightingModel();
		ShaderLoader::loadUniform1f(*m_shader, EntityShaderConstants::FRAG_AMBIENT, lightingModel->getAmbient());
		ShaderLoader::loadUniform1f(*m_shader, EntityShaderConstants::FRAG_EMISSIVE, lightingModel->getEmissive());
		ShaderLoader::loadUniform1f(*m_shader, EntityShaderConstants::FRAG_DIFFUSE, lightingModel->getDiffuse());
		ShaderLoader::loadUniform1f(*m_shader, EntityShaderConstants::FRAG_SPECULAR, lightingModel->getSpecular());
		ShaderLoader::loadUniform1f(*m_shader, EntityShaderConstants::FRAG_SPECULAR_HIGHLIGHT, lightingModel->getSpecularHighlight());
		ShaderLoader::loadUniform1f(*m_shader, EntityShaderConstants::FRAG_REFLECTIVITY, lightingModel->getReflectivity());
		ShaderLoader::loadUniform1f(*m_shader, EntityShaderConstants::FRAG_REFRACTIVE_INDEX, lightingModel->getRefractiveIndex());
		ShaderLoader::loadUniform1f(*m_shader, EntityShaderConstants::FRAG_OPACITY, lightingModel->getOpacity());

		// Stop shader
		ShaderLoader::stopShader(*m_shader);
	}

	void EntityRenderer::render(const Models::Entity & entity) const
	{
		// Render the currently loaded entity
		ShaderLoader::startShader(*m_shader);
		glDrawElements(GL_TRIANGLES, entity.getRenderModel()->getGeometryModel()->getIndices()->size(), GL_UNSIGNED_INT, 0);
		ShaderLoader::stopShader(*m_shader);
	}

	void EntityRenderer::unloadRenderModel() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glBindVertexArray(0);
	}



	EntityRenderer & EntityRenderer::operator=(const EntityRenderer & other)
	{
		m_shader = other.m_shader;

		return *this;
	}




}
