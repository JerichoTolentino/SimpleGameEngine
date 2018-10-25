#include "EntityRenderer.h"
#include "../entities/BoundingBox.h"



EntityRenderer::EntityRenderer()
{
	MessageHandler::printMessage("ERROR: Default constructor for EntityRenderer called! (Need shader file paths)\n");
	system("PAUSE");
}


EntityRenderer::~EntityRenderer()
{
}

EntityRenderer::EntityRenderer(const char* vertexShader, const char* fragmentShader)
{
	shader = Shader(vertexShader, fragmentShader);
}

void EntityRenderer::loadEntity(Entity* entity, Skybox* skybox) const
{
	Model* model = entity->getModel();

	glBindVertexArray(model->getVAO());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	shader.start();
	shader.loadUniformMat4f(entity->generateTransformationMatrix(), "model_matrix");

	if (model->getMaterial() != NULL)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, model->getMaterial()->getTextureID());
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->getTextureID());

		shader.loadUniform1f(model->getMaterial()->getAmbient(), "ka");
		//shader.loadUniform1f(model.getMaterial().getEmissive(), "ke");
		shader.loadUniform1f(model->getMaterial()->getDiffuse(), "kd");
		shader.loadUniform1f(model->getMaterial()->getSpecular(), "ks");
		shader.loadUniform1f(model->getMaterial()->getSpecularHighlight(), "sh");
		shader.loadUniform1f(model->getMaterial()->getReflectivity(), "r");
		//shader.loadUniform1f(model.getMaterial().getRefractiveIndex(), "n");
		shader.loadUniform1f(model->getMaterial()->getOpacity(), "o");
	}
	else
		MessageHandler::printMessage("ERROR: No material found in entity!\n");

	shader.stop();
}

void EntityRenderer::render(Entity* e) const
{
	shader.start();
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
	shader.stop();
}

void EntityRenderer::unloadEntity() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glBindVertexArray(0);
}

void EntityRenderer::loadProjectionMatrix(Mat4 proj) const
{
	shader.start();
	shader.loadUniformMat4f(proj, "proj_matrix");
	shader.stop();
}

void EntityRenderer::loadCamera(Camera* camera) const
{
	shader.start();
	shader.loadUniformVec3f(camera->getPosition(), "eyePos");
	shader.loadUniformMat4f(camera->generateViewMatrix(), "view_matrix");
	shader.stop();
}

void EntityRenderer::loadLight(Vec3 light) const
{
	shader.start();
	shader.loadUniformVec3f(light, "lightPos");
	shader.stop();
}
