#pragma once
#include <map>
#include <vector>
#include <iostream>
#include "../entities/Entity.h"
#include "EntityRenderer.h"
#include "TerrainRenderer.h"
#include "SkyboxRenderer.h"

class RenderEngine
{
private:
	std::map<Model*, std::vector<Entity*>*> *entities;
	std::map<Model*, std::vector<Terrain*>*> *terrains;
	Skybox *skybox;		//TODO: Add support for multiple skyboxes (want more than 1 world...)
	EntityRenderer *entityRenderer;
	TerrainRenderer *terrainRenderer;
	SkyboxRenderer *skyboxRenderer;

	//FOR DEBUG
	static bool DEBUG_RAY;
	static Vec3 rayStartPos;
	static Vec3 rayDir;
	//END FOR DEBUG

public:
	RenderEngine();
	~RenderEngine();

	std::map<Model*, std::vector<Entity*>*> * getEntitiesMap() const;
	std::map<Model*, std::vector<Terrain*>*> * getTerrainsMap() const;

	void loadProjectionMatrix(Mat4 proj);
	void loadEntity(Entity* e);
	void loadTerrain(Terrain *t);
	void loadSkybox(Skybox *sb);
	
	//FOR DEBUG
	static void drawRay(const Vec3 &ray, const Vec3 &startPos, bool draw);
	//END FOR DEBUG

	void render(Camera *camera, Vec3 light) const;
};

