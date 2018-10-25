#include "RenderEngine.h"

//FOR DEBUG
bool RenderEngine::DEBUG_RAY = false;
Vec3 RenderEngine::rayStartPos;
Vec3 RenderEngine::rayDir;
//END FOR DEBUG

RenderEngine::RenderEngine()
{
	entities = new std::map<Model*, std::vector<Entity*>*>;
	terrains = new std::map<Model*, std::vector<Terrain*>*>;
	entityRenderer = new EntityRenderer("src/shaders/entityVertex.vert", "src/shaders/entityFragment.frag");
	terrainRenderer = new TerrainRenderer("src/shaders/terrainVertex.vert", "src/shaders/terrainFragment.frag");
	skyboxRenderer = new SkyboxRenderer("src/shaders/skyboxVertex.vert", "src/shaders/skyboxFragment.frag");
}

RenderEngine::~RenderEngine()
{
	delete entities;
	delete entityRenderer;
	delete terrainRenderer;
	delete skyboxRenderer;
}

std::map<Model*, std::vector<Entity*>*>* RenderEngine::getEntitiesMap() const
{
	return entities;
}

std::map<Model*, std::vector<Terrain*>*>* RenderEngine::getTerrainsMap() const
{
	return terrains;
}

void RenderEngine::loadProjectionMatrix(Mat4 proj)
{
	entityRenderer->loadProjectionMatrix(proj);
	terrainRenderer->loadProjectionMatrix(proj);
	skyboxRenderer->loadProjectionMatrix(proj);
}

void RenderEngine::loadEntity(Entity* e)
{
	//std::cout << e->toString() << std::endl;
	std::vector<Entity*> *vectorEntity = (*entities)[e->getModel()];
	if (vectorEntity)
	{
		vectorEntity->push_back(e);
	}
	else
	{
		vectorEntity = new std::vector<Entity*>;
		vectorEntity->push_back(e);
		(*entities)[e->getModel()] = vectorEntity;
	}

	//std::cout << (*entities)[e->getModel()]->front()->toString() << (*entities)[e->getModel()]->back()->toString() << std::endl;
}

void RenderEngine::loadTerrain(Terrain * t)
{
	//std::cout << t->toString() << std::endl;
	std::vector<Terrain*> *vectorTerrain = (*terrains)[t->getModel()];
	if (vectorTerrain)
	{
		vectorTerrain->push_back(t);
	}
	else
	{
		vectorTerrain = new std::vector<Terrain*>;
		vectorTerrain->push_back(t);
		(*terrains)[t->getModel()] = vectorTerrain;
	}
}

void RenderEngine::loadSkybox(Skybox * sb)
{
	MessageHandler::printMessage(sb->toString() + "\n");
	skybox = sb;
}

//FOR DEBUG
void RenderEngine::drawRay(const Vec3 & ray, const Vec3 & startPos, bool draw)
{
	RenderEngine::DEBUG_RAY = true;
	RenderEngine::rayStartPos = startPos;
	RenderEngine::rayDir = ray;
}

void RenderEngine::render(Camera *camera, Vec3 light) const
{
	//DEBUG render ray
	if (DEBUG_RAY)
	{
		Vec3 endPos = rayStartPos + rayDir.multiply(rayStartPos).multiply(100);
		MessageHandler::printMessage("Start: " + rayStartPos.toString() + "\nEnd: " + endPos.toString());
		glBegin(GL_LINES);
		glVertex3f(rayStartPos.x, rayStartPos.y, rayStartPos.z);
		glVertex3f(endPos.x, endPos.y, endPos.z);
		glEnd();
	}

	//render terrain(s)
	for (std::map<Model*, std::vector<Terrain*>*>::iterator iter = terrains->begin(); iter != terrains->end(); iter++)
	{
		std::vector<Terrain*> *terrainList = iter->second;
		for (unsigned int i = 0; i < terrainList->size(); i++)
		{
			Terrain *terrain = terrainList->at(i);
			terrainRenderer->loadCamera(camera);
			terrainRenderer->loadLight(light);
			terrainRenderer->loadTerrain(terrain);
			terrainRenderer->render(terrain);
			terrainRenderer->unloadTerrain();
		}
	}
	
	//render entities
	for (std::map<Model*, std::vector<Entity*>*>::iterator iter = entities->begin(); iter != entities->end(); iter++)
	{
		std::vector<Entity*> *entityList = iter->second;
		for (unsigned int i = 0; i < entityList->size(); i++)
		{
			Entity *entity = entityList->at(i);
			entityRenderer->loadCamera(camera);
			entityRenderer->loadLight(light);
			entityRenderer->loadEntity(entity, skybox);
			entityRenderer->render(entity);
			entityRenderer->unloadEntity();
		}
	}

	//render skybox
	skyboxRenderer->loadCamera(camera);
	if (skybox)
	{
		skyboxRenderer->loadSkybox(skybox);
		skyboxRenderer->render(skybox);
		skyboxRenderer->unloadSkybox();
	}
}
