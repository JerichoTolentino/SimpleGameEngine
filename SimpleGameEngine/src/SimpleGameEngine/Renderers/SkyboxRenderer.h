#pragma once
#include "../loaders/Shader.h"
#include "../skybox/Skybox.h"
#include "../entities/Camera.h"

class SkyboxRenderer
{
private:
	Shader m_shader;

public:
	SkyboxRenderer();
	~SkyboxRenderer();

	SkyboxRenderer(const char* vertexShader, const char* fragmentShader);

	void loadSkybox(Skybox* skybox) const;
	void render(Skybox* sb) const;
	void unloadSkybox() const;
	void loadProjectionMatrix(Mat4 proj) const;
	void loadCamera(Camera* camera) const;
};

