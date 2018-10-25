#pragma once
#include <iostream>
#include "../entities/Entity.h"
#include "../entities/Camera.h"
#include "../loaders/Shader.h"
#include "../skybox/Skybox.h"

#define DEBUG_BOUNDING_BOX true

class EntityRenderer
{
private:
	Shader shader;
public:
	EntityRenderer();
	~EntityRenderer();

	EntityRenderer(const char* vertexShader, const char* fragmentShader);

	void loadEntity(Entity* entity, Skybox* skybox) const;
	void render(Entity* e) const;
	void unloadEntity() const;
	void loadProjectionMatrix(Mat4 proj) const;
	void loadCamera(Camera* camera) const;
	void loadLight(Vec3 light) const;
};

