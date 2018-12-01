#include "Application.h"
#include <memory>
#include "Display/Window.h"
#include "Parsers/WavefrontObjParser.h"
#include "Parsers/MaterialLibraryParser.h"
#include "Parsers/ParseException.h"
#include "Loaders/Loader.h"
#include "Loaders/ShaderLoader.h"
#include "Models/RenderModel.h"
#include "Renderers/RenderEngine.h"
#include "Shaders/Shader.h"
#include "Models/TerrainRenderModel.h"
#include "Models/SkyboxRenderModel.h"
#include "Models/HeightMap.h"
#include "Models/LightSource.h"
#include "Math/Vec3.h"
#include "Log.h"
#include "Logic/ModelTransformer.h"

using namespace SimpleGameEngine::Cameras;
using namespace SimpleGameEngine::Display;
using namespace SimpleGameEngine::Parsers;
using namespace SimpleGameEngine::Loaders;
using namespace SimpleGameEngine::Renderers;
using namespace SimpleGameEngine::Models;
using namespace SimpleGameEngine::Shaders;
using namespace SimpleGameEngine::Math;
using namespace SimpleGameEngine::Logic;

namespace SimpleGameEngine
{
	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{
		try
		{
			// Initialize window - also initializes GLEW and GLFW
			Window window;

			// Make shaders
			auto entityShader = std::make_shared<Shader>(ShaderLoader::loadShader(
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/src/SimpleGameEngine/Shaders/entityVertex.vert", 
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/src/SimpleGameEngine/Shaders/entityFragment.frag"));
			auto terrainShader = std::make_shared<Shader>(ShaderLoader::loadShader(
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/src/SimpleGameEngine/Shaders/terrainVertex.vert", 
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/src/SimpleGameEngine/Shaders/terrainFragment.frag"));
			auto skyboxShader = std::make_shared<Shader>(ShaderLoader::loadShader(
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/src/SimpleGameEngine/Shaders/skyboxVertex.vert", 
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/src/SimpleGameEngine/Shaders/skyboxFragment.frag"));

			// Make renderers
			auto entityRenderer = std::make_shared<EntityRenderer>(EntityRenderer(entityShader));
			auto terrainRenderer = std::make_shared<TerrainRenderer>(TerrainRenderer(terrainShader));
			auto skyboxRenderer = std::make_shared<SkyboxRenderer>(SkyboxRenderer(skyboxShader));
			RenderEngine renderEngine(entityRenderer, terrainRenderer, skyboxRenderer);

			// Build scene
			RenderScene scene;

			// Load projection matrix
			int windowWidth, windowHeight;
			window.getWindowSize(windowWidth, windowHeight);
			float aspectRatio = windowHeight == 0 ? 1 : (float) windowWidth / windowHeight;
			auto projectionMatrix = std::make_shared<Mat4>(Mat4::generateProjectionMatrix(aspectRatio, 90, 0.1f, 1000.0f));
			scene.setProjectionMatrix(projectionMatrix);

			// Create terrain
			auto texturePack = std::make_shared<TexturePack>(Loader::loadTexturePack(
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/brickPath.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/broken_pavement.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/cobble.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/dirt.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/zombieBlendMap.png"));
			auto terrainSpace = std::make_shared<SpaceModel>(SpaceModel(Vec3(0, -20, 0), Vec3(0, 0, 0), Vec3(1, 1, 1)));
			auto terrainMaterial = std::make_shared<Material>(std::make_shared<LightingModel>(LightingModel(0.0f, 1, 0.1f, 0, 0.8f, 0.0f, 0.0f, 0)));
			auto heightMap = std::make_shared<HeightMap>(Loader::loadHeightMap("C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/zombieHeightMap.png", 20));
			auto terrainModel = std::make_shared<TerrainModel>(TerrainModel::GenerateTerrainModel(1, 20, heightMap));
			GLuint terrainVaoId = Loader::loadGeometryModel(*(terrainModel->getGeometryModel()));
			auto terrainRenderModel = std::make_shared<TerrainRenderModel>(TerrainRenderModel(terrainModel, terrainMaterial, terrainSpace, texturePack, terrainVaoId));
			ModelTransformer::translate(*terrainSpace, Vec3(-heightMap->getWidth() / 2.0f, 0, -heightMap->getHeight() / 2.0f));
			scene.addTerrain(terrainRenderModel);

			// Create skybox
			auto skyboxModel = std::make_shared<SkyboxModel>(SkyboxModel::CreateSkyboxModel(500));
			GLuint skyboxVaoId = Loader::loadSkybox(*skyboxModel);
			GLuint skyboxTextureId = Loader::loadCubemapTexture(
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/Lycksele3/posx.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/Lycksele3/negx.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/Lycksele3/posy.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/Lycksele3/negy.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/Lycksele3/posz.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/Lycksele3/negz.jpg"
			);
			auto skyboxRenderModel = std::make_shared<SkyboxRenderModel>(SkyboxRenderModel(skyboxModel, skyboxVaoId, skyboxTextureId));
			scene.setSkybox(skyboxRenderModel);

			// Create stall entity
			auto stallModel = std::make_shared<GeometryModel>(WavefrontObjParser::parseFile("D:/Blender Files/stall.obj"));
			auto stallMaterial = std::make_shared<Material>(std::make_shared<LightingModel>(LightingModel(0.0f, 1.0f, 0.1f, 0, 1.0f, 1.0f, 32, 1.33f)));
			unsigned int stallModelId = Loader::loadGeometryModel(*stallModel);
			unsigned int stallTextureId = Loader::loadTexture("D:/Blender Files/stallTexture.png");
			auto stallRenderModel = std::make_shared<RenderModel>(RenderModel(stallModel, stallMaterial, stallModelId, stallTextureId, skyboxTextureId));
			auto stallSpaceModel = std::make_shared<SpaceModel>(SpaceModel(Vec3(5, -3, -10), Vec3(0, 180, 0), Vec3(1, 1, 1)));
			auto stallEntity = std::make_shared<Entity>(Entity(stallRenderModel, stallSpaceModel));
			scene.addEntity(stallEntity);

			// Create ugly water bottle entity
			auto waterBottleModel = std::make_shared<GeometryModel>(WavefrontObjParser::parseFile("D:/Blender Files/UglyWaterBottle.obj"));
			auto waterBottleMaterial = std::make_shared<Material>(std::make_shared<LightingModel>(LightingModel(0, 1, 0.1f, 0, 1.0f, 0.4f, 32, 1.5f)));
			unsigned int waterBottleModelId = Loader::loadGeometryModel(*waterBottleModel);
			unsigned int waterBottleTextureId = Loader::loadTexture("D:/Blender Files/WaterBottleTexture.png");
			auto waterBottleRenderModel = std::make_shared<RenderModel>(RenderModel(waterBottleModel, waterBottleMaterial, waterBottleModelId, waterBottleTextureId, skyboxTextureId));
			auto waterBottleSpaceModel = std::make_shared<SpaceModel>(SpaceModel(Vec3(-5, -3, -10), Vec3(0, 0, 0), Vec3(1, 1, 1)));
			auto waterBottleEntity = std::make_shared<Entity>(Entity(waterBottleRenderModel, waterBottleSpaceModel));
			scene.addEntity(waterBottleEntity);

			// Create camera
			std::shared_ptr<Camera> camera = std::make_shared<Camera>(Camera(Vec3(0, 0.2f, 0), Vec3(-0.2f, 0, 0)));
			scene.setCamera(camera);

			// Create lights
			auto lightSources = std::vector<std::shared_ptr<Models::LightSource>>();
			auto testLight = std::make_shared<LightSource>(LightSource(Vec3(-30, 0.2f, 0), Vec3(1, 0, 0), Vec3(1, 0.01f, 0.002f)));
			//lightSources.push_back(std::make_shared<LightSource>(LightSource(Vec3(-1000, 1000, -1000), Vec3(1, 1, 1))));
			lightSources.push_back(testLight);
			//lightSources.push_back(std::make_shared<LightSource>(LightSource(Vec3(5, 2, -10), Vec3(0, 0, 1), Vec3(1, 0.01f, 0.002f))));
			//lightSources.push_back(std::make_shared<LightSource>(LightSource(Vec3(-50, 2, -100), Vec3(0, 1, 0), Vec3(1, 0.01f, 0.002f))));
			for (auto light : lightSources)
			{
				scene.addLight(light);
			}
			
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);

			renderEngine.loadScene(scene);

			bool goLeft = false;

			// Main loop
			while (!window.isClosed())
			{
				window.clear();

				ModelTransformer::rotate(*waterBottleSpaceModel, Vec3(0, 0.5f, 0));
				renderEngine.render();

				if (testLight->getPosition().x < -30)
					goLeft = false;
				else if (testLight->getPosition().x > 30)
					goLeft = true;

				if (goLeft)
					testLight->translate(Vec3(-0.5f, 0, 0));
				else
					testLight->translate(Vec3(0.5f, 0, 0));
				

				//camera->setRotation(camera->getRotation().add(Vec3(0, 0.5f, 0)));

				window.update();
			}
		}
		catch (std::exception e)
		{
			SGE_ERROR("Unexpected error: " + std::string(e.what()));
		}

		std::cout << "Press enter to exit." << std::endl;
		std::cin.get();
	}
}
