#include "TerrainRenderer.h"


TerrainRenderer::TerrainRenderer()
{
	MessageHandler::printMessage("ERROR: Default constructor for TerrainRenderer called! (Need shader file paths)\n");
	system("PAUSE");
}

TerrainRenderer::~TerrainRenderer()
{
}

TerrainRenderer::TerrainRenderer(const char * vertexShader, const char * fragmentShader)
{
	m_shader = Shader(vertexShader, fragmentShader);
}

void TerrainRenderer::loadTerrain(Terrain * terrain) const
{
	Model* model = terrain->getModel();

	glBindVertexArray(model->getVAO());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	m_shader.start();
	m_shader.loadUniformMat4f(terrain->generateTransformationMatrix(), "model_matrix");
	m_shader.loadUniform1f(terrain->getTileFactor(), "tileFactor");

	TexturePack *texturePack = terrain->getTexturePack();
	if (texturePack != NULL)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texturePack->getBlendMapTextureID());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texturePack->getRedTextureID());
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, texturePack->getGreenTextureID());
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, texturePack->getBlueTextureID());
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, texturePack->getBackTextureID());

		m_shader.loadUniform1i(0, "blendSampler");
		m_shader.loadUniform1i(1, "redSampler");
		m_shader.loadUniform1i(2, "greenSampler");
		m_shader.loadUniform1i(3, "blueSampler");
		m_shader.loadUniform1i(4, "backSampler");
	}
	else
	{
	}

	if (model->getMaterial() != NULL)
	{
		//glActiveTexture(GL_TEXTURE0);
	//	glBindTexture(GL_TEXTURE_2D, model->getMaterial()->getTextureID());

		m_shader.loadUniform1f(model->getMaterial()->getAmbient(), "ka");
		m_shader.loadUniform1f(model->getMaterial()->getDiffuse(), "kd");
		m_shader.loadUniform1f(model->getMaterial()->getOpacity(), "o");
	}
	else
		MessageHandler::printMessage("ERROR: No material found in terrain!\n");

	m_shader.stop();
}

void TerrainRenderer::render(Terrain * t) const
{
	m_shader.start();
	glDrawElements(GL_TRIANGLES, t->getModel()->getNumIndices(), GL_UNSIGNED_INT, 0);
	m_shader.stop();
}

void TerrainRenderer::unloadTerrain() const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);
}

void TerrainRenderer::loadProjectionMatrix(Mat4 proj) const
{
	m_shader.start();
	m_shader.loadUniformMat4f(proj, "proj_matrix");
	m_shader.stop();
}

void TerrainRenderer::loadCamera(Camera * camera) const
{
	m_shader.start();
	m_shader.loadUniformMat4f(camera->generateViewMatrix(), "view_matrix");
	m_shader.stop();
}

void TerrainRenderer::loadLight(Vec3 light) const
{
	m_shader.start();
	m_shader.loadUniformVec3f(light, "lightPos");
	m_shader.stop();
}
