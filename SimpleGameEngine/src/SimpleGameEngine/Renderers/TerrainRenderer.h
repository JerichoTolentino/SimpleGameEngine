#pragma once
#include "../loaders/Shader.h"
#include "../math/engineMath.h"
#include "../terrains/Terrain.h"
#include "../entities/Camera.h"

class TerrainRenderer
{
private:
	Shader shader;
public:
	TerrainRenderer();
	~TerrainRenderer();

	TerrainRenderer(const char* vertexShader, const char* fragmentShader);

	void loadTerrain(Terrain* terrain) const;
	void render(Terrain* t) const;
	void unloadTerrain() const;
	void loadProjectionMatrix(Mat4 proj) const;
	void loadCamera(Camera* camera) const;
	void loadLight(Vec3 light) const;
};

