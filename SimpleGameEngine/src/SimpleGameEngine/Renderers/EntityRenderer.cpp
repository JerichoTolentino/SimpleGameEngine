#include "EntityRenderer.h"

using namespace SimpleGameEngine::Shaders;

namespace SimpleGameEngine::Renderers
{
	EntityRenderer::EntityRenderer(Shader shader)
	{
		m_shader = shader;
	}

	EntityRenderer::~EntityRenderer()
	{
	}



	void EntityRenderer::loadEntity(Entity* entity, Skybox* skybox) const
	{
		Model* model = entity->getModel();

		glBindVertexArray(model->getVAO());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		m_shader.start();
		m_shader.loadUniformMat4f(entity->generateTransformationMatrix(), "model_matrix");

		if (model->getMaterial() != NULL)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, model->getMaterial()->getTextureID());
			glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->getTextureID());

			m_shader.loadUniform1f(model->getMaterial()->getAmbient(), "ka");
			//m_shader.loadUniform1f(model.getMaterial().getEmissive(), "ke");
			m_shader.loadUniform1f(model->getMaterial()->getDiffuse(), "kd");
			m_shader.loadUniform1f(model->getMaterial()->getSpecular(), "ks");
			m_shader.loadUniform1f(model->getMaterial()->getSpecularHighlight(), "sh");
			m_shader.loadUniform1f(model->getMaterial()->getReflectivity(), "r");
			//m_shader.loadUniform1f(model.getMaterial().getRefractiveIndex(), "n");
			m_shader.loadUniform1f(model->getMaterial()->getOpacity(), "o");
		}
		else
			MessageHandler::printMessage("ERROR: No material found in entity!\n");

		m_shader.stop();
	}

	void EntityRenderer::render(Entity* e) const
	{
		m_shader.start();
		glDrawElements(GL_TRIANGLES, e->getModel()->getNumIndices(), GL_UNSIGNED_INT, 0);
		//TODO: render bbox here if DEBUG_BOUNDING_BOX is enabled
		if (DEBUG_BOUNDING_BOX)
		{
			//TODO: CHECK IF INCLUDING BOUNDING BOX causes circular includes
			//THIS IS NOT THE A GOOD SOLUTION AT ALL
			GLfloat *vertices = const_cast<BoundingBox*>(e->getBoundingBox())->generateVertices();
			GLuint *indices = const_cast<BoundingBox*>(e->getBoundingBox())->generateIndices();
			GLuint index = indices[0];
			glBegin(GL_LINES);
			for (int i = 0; i < 24; i++)
			{
				index = indices[i];
				glVertex3f(vertices[index * 3] / e->getScale().x - e->getPosition().x, vertices[index * 3 + 1] / e->getScale().y - e->getPosition().y, vertices[index * 3 + 2] / e->getScale().z - e->getPosition().z);
			}
			glEnd();
		}
		m_shader.stop();
	}

	void EntityRenderer::unloadEntity() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glBindVertexArray(0);
	}

	void EntityRenderer::loadProjectionMatrix(Mat4 proj) const
	{
		m_shader.start();
		m_shader.loadUniformMat4f(proj, "proj_matrix");
		m_shader.stop();
	}

	void EntityRenderer::loadCamera(Camera* camera) const
	{
		m_shader.start();
		m_shader.loadUniformVec3f(camera->getPosition(), "eyePos");
		m_shader.loadUniformMat4f(camera->generateViewMatrix(), "view_matrix");
		m_shader.stop();
	}

	void EntityRenderer::loadLight(Vec3 light) const
	{
		m_shader.start();
		m_shader.loadUniformVec3f(light, "lightPos");
		m_shader.stop();
	}
}
