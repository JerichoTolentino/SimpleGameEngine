/*
AUTHOR: Jericho Tolentino

This my attempt at building my own simple OpenGL game engine, inspired by a 
functionally limited OpenGL game engine I created for a university course project
*/

#include "src/display/window.h"
#include "src/math/engineMath.h"
#include "src/entities/Entity.h"
#include "src/entities/Camera.h"
#include "src/loaders/Loader.h"
#include "src/loaders/Shader.h"
#include "src/loaders/ObjectFileLoader.h"
#include "src/renderer/EntityRenderer.h"
#include "src/renderer/RenderEngine.h"
#include "src/entities/DynamicEntity.h"
#include "src/characters/Character.h"
#include "src/terrains/Terrain.h"
#include "src/skybox/Skybox.h"
#include "src/controllers/Controller.h"
#include "src/controllers/RayCaster.h"
#include "src/entities/BoundingBox.h"
#include "src/utils/MessageHandler.h"

#include <iostream>
#include <fstream>

int main()
{
	system("PAUSE");

	/*
	All of this initialization code will be factored out of here eventually..
	most of this is just for debugging anyway
	*/

	//Window window;
	Window window(800, 800);

	Loader loader;
	RenderEngine renderEngine;

	int wWidth, wHeight;
	window.getWindowSize(wWidth, wHeight);

	float aspect;
	if (wHeight != 0)
		aspect = (float)wWidth / wHeight;
	else
		aspect = 1;

	Mat4 projection = Mat4::generateProjectionMatrix(aspect, 90, 0.1f, 1000.0f);
	renderEngine.loadProjectionMatrix(projection);

	Vec3 lightPos(0, 100, 2);
	Camera* camera = new Camera;

	Skybox *skybox = new Skybox("res/textures/Lycksele3/posx.jpg", "res/textures/Lycksele3/negx.jpg", "res/textures/Lycksele3/posy.jpg", "res/textures/Lycksele3/negy.jpg", "res/textures/Lycksele3/posz.jpg", "res/textures/Lycksele3/negz.jpg");

	renderEngine.loadSkybox(skybox);

	TexturePack *texturePack = new TexturePack("res/textures/brickPath.jpg", "res/textures/broken_pavement.jpg", "res/textures/cobble.jpg", "res/textures/dirt.jpg", "res/textures/zombieBlendMap.png");
	HeightMap *heightMap = new HeightMap("res/textures/zombieHeightMap.png");
	Terrain *terrain = new Terrain(Vec3(-100, -2, -100), 1, 20, 20, 20, texturePack, heightMap);
	//Terrain *terrain = new Terrain(Vec3(0, -2, 0), 1, 20, 20, 20, texturePack, heightMap);

	terrain->getModel()->getMaterial()->setTextureID(Loader::loadTexture("res/textures/brickPath.jpg"));
	renderEngine.loadTerrain(terrain);

	DynamicEntity* entity = new DynamicEntity(ObjectFileLoader::loadOBJ("res/models/sphere.obj", "res/textures/texturedCube.png"), Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(1, 1, 1), 0.01f, 0.5f);
	//DynamicEntity* entity = new DynamicEntity(ObjectFileLoader::loadOBJ("res/models/texturedCube.obj", "res/textures/texturedCube.png"), Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(1, 1, 1), 0.01f, 0.5f);
	//entity->setPosition(Vec3(-3, terrain->getHeight(Vec3(-3, 0, -5.0)), -5.0f));
	entity->setPosition(Vec3(0, terrain->getHeight(entity->getPosition()), 0));
	DynamicEntity* entity2 = new DynamicEntity(*entity);
	entity2->setModel(new Model(*entity->getModel()));
	entity2->getModel()->setMaterial(new Material(*entity->getModel()->getMaterial()));
	entity2->getModel()->getMaterial()->setReflectivity(1.0f);
	entity2->setPosition(Vec3(3, terrain->getHeight(Vec3(3, 0, -5.0)), -5.0f));
	DynamicEntity* stall = new  DynamicEntity(ObjectFileLoader::loadOBJ("res/models/lamp.obj", "res/textures/lampTexture.png"), Vec3(0, -2, -5), Vec3(0, 180, 0), Vec3(1, 3, 1), 0.01f, 0.5f);
	DynamicEntity* human = new DynamicEntity(ObjectFileLoader::loadOBJ("res/models/untitled.obj", "res/textures/character.png"), Vec3(0, terrain->getHeight(Vec3(0, 0, 0)), 0), Vec3(0, 0, 0), Vec3(0.3f, 0.4f, 0.3f), 10, 80);
	Character *character = new Character(1, 100, 100, 100, "Jericho", "Human", human);

	Model* model = entity->getModel();
	model->getMaterial()->setSpecular(0.7f);
	model->getMaterial()->setSpecularHighlight(27.0f);
	model->getMaterial()->setTextureID(Loader::loadTexture("res/textures/shinyObjectTexture.png"));
	model->getMaterial()->setReflectivity(0.3f);

	model = stall->getModel();
	model->getMaterial()->setSpecular(0.9f);
	model->getMaterial()->setSpecularHighlight(270.0f);
	model->getMaterial()->setTextureID(Loader::loadTexture("res/textures/lampTexture.png"));
	model->getMaterial()->setReflectivity(0.5f);
	
	model = human->getModel();
	model->getMaterial()->setSpecular(0.0f);
	model->getMaterial()->setSpecularHighlight(270.0f);
	model->getMaterial()->setTextureID(Loader::loadTexture("res/textures/character.png"));

	MessageHandler::printMessage(entity->getBoundingBox()->toString());
	MessageHandler::printMessage(entity->getModel()->getMaterial()->toString());
	MessageHandler::printMessage(stall->getModel()->getMaterial()->toString());
	renderEngine.loadEntity(entity);
	renderEngine.loadEntity(entity2);
	renderEngine.loadEntity(stall);
	//renderEngine.loadEntity(character->getEntity());
	
	Controller controller(character, camera, &window, renderEngine.getEntitiesMap());

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	
	//system("PAUSE");

	Mat4 matrix;
	float values[16] = {
		0,2,8,6,
		3,7,1,0,
		0,0,1,2,
		0,1,0,1
	};
	matrix.setElements(values);
	std::cout << matrix.toString() << "\n";
	matrix.inverse();
	std::cout << "Inverse: " << matrix.toString() << "\n";

	//main game loop
	while (!window.isClosed())
	{
		window.clear();

		//camera->moveCamera(window, terrain);

		controller.readInput(window, terrain, projection, camera);

		renderEngine.render(camera, lightPos);

		if (window.isKeyDown(GLFW_KEY_ESCAPE))
			break;

		window.update();
	}

	window.forceClose();

	system("PAUSE");

	return 0;
}