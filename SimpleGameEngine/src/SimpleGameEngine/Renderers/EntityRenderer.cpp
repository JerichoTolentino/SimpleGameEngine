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

	void EntityRenderer::loadLight(const Math::Vec3 & light) const
	{
		ShaderLoader::startShader(*m_shader);
		ShaderLoader::loadUniformVec3f(*m_shader, EntityShaderConstants::VERT_LIGHT_POSITION, light);
		ShaderLoader::stopShader(*m_shader);
	}

	void EntityRenderer::loadProjectionMatrix(const Math::Mat4 & proj) const
	{
		ShaderLoader::startShader(*m_shader);
		ShaderLoader::loadUniformMat4f(*m_shader, EntityShaderConstants::VERT_PROJECTION_MATRIX, proj);
		ShaderLoader::stopShader(*m_shader);
	}

	void EntityRenderer::loadEntity(const Models::Entity & entity) const
	{
		// Bind the geometry model's VAO
		glBindVertexArray(entity.getRenderModel()->getGeometryVaoId());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// Startup shader
		ShaderLoader::startShader(*m_shader);

		// Load in the entity's transformation
		auto spaceModel = entity.getSpaceModel();
		Mat4 entityTransform;
		entityTransform.setIdentity();
		entityTransform.transform(spaceModel->getPosition(), spaceModel->getRotation(), spaceModel->getScale());
		ShaderLoader::loadUniformMat4f(*m_shader, EntityShaderConstants::VERT_MODEL_MATRIX, entityTransform);

		// Bind the entity's texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, entity.getRenderModel()->getTextureId());

		// Load in the entity's material
		auto lightingModel = entity.getRenderModel()->getMaterial()->getLightingModel();
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

	void EntityRenderer::loadEntity(const Models::Entity & entity, GLuint reflectionMapTextureId) const
	{
		// Bind the geometry model's VAO
		glBindVertexArray(entity.getRenderModel()->getGeometryVaoId());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		// Startup shader
		ShaderLoader::startShader(*m_shader);

		// Load in the entity's transformation
		auto spaceModel = entity.getSpaceModel();
		Mat4 entityTransform;
		entityTransform.setIdentity();
		entityTransform.transform(spaceModel->getPosition(), spaceModel->getRotation(), spaceModel->getScale());
		ShaderLoader::loadUniformMat4f(*m_shader, EntityShaderConstants::VERT_MODEL_MATRIX, entityTransform);

		// Bind the entity's texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, entity.getRenderModel()->getTextureId());
		glBindTexture(GL_TEXTURE_CUBE_MAP, reflectionMapTextureId);

		// Load in the entity's material
		auto lightingModel = entity.getRenderModel()->getMaterial()->getLightingModel();
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

	void EntityRenderer::unloadEntity() const
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
