#include "SkyboxRenderer.h"



SkyboxRenderer::SkyboxRenderer()
{
	MessageHandler::printMessage("ERROR: Default constructor for SkyboxRenderer called! (Need shader file paths)\n");
	system("PAUSE");
}


SkyboxRenderer::~SkyboxRenderer()
{
}

SkyboxRenderer::SkyboxRenderer(const char * vertexShader, const char * fragmentShader)
{
	shader = Shader(vertexShader, fragmentShader);
}

void SkyboxRenderer::loadSkybox(Skybox * skybox) const
{
	glBindVertexArray(skybox->getVAO());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->getTextureID());
}

void SkyboxRenderer::render(Skybox * sb) const
{
	glDisable(GL_CULL_FACE);
	shader.start();
	glDrawElements(GL_TRIANGLES, sb->getNumIndices(), GL_UNSIGNED_INT, 0);
	shader.stop();
	glEnable(GL_CULL_FACE);
}

void SkyboxRenderer::unloadSkybox() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glBindVertexArray(0);
}

void SkyboxRenderer::loadProjectionMatrix(Mat4 proj) const
{
	shader.start();
	shader.loadUniformMat4f(proj, "proj_matrix");
	shader.stop();
}

void SkyboxRenderer::loadCamera(Camera * camera) const
{
	shader.start();
	shader.loadUniformMat4f(camera->generateSkyboxViewMatrix(), "view_matrix");
	shader.stop();
}
