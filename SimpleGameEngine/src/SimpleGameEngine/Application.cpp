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

			// Load projection matrix
			int windowWidth, windowHeight;
			window.getWindowSize(windowWidth, windowHeight);
			float aspectRatio = windowHeight == 0 ? 1 : (float) windowWidth / windowHeight;
			Mat4 projectionMatrix = Mat4::generateProjectionMatrix(aspectRatio, 90, 0.1f, 1000.0f);
			renderEngine.loadProjectionMatrix(projectionMatrix);

			// Create terrain
			auto texturePack = std::make_shared<TexturePack>(Loader::loadTexturePack(
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/brickPath.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/broken_pavement.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/cobble.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/dirt.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/zombieBlendMap.png"));
			auto terrainSpace = std::make_shared<SpaceModel>(SpaceModel(Vec3(-100, -2, -100), Vec3(0, 0, 0), Vec3(1, 1, 1)));
			auto terrainMaterial = std::make_shared<Material>(MaterialLibraryParser::parseFile("D:/Blender Files/Cube.mtl"));
			auto heightMap = std::make_shared<HeightMap>(Loader::loadHeightMap("C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/zombieHeightMap.png", 20));
			auto terrainModel = std::make_shared<TerrainModel>(TerrainModel::GenerateTerrainModel(1, heightMap));
			GLuint terrainVaoId = Loader::loadGeometryModel(*(terrainModel->getGeometryModel()));
			auto terrainRenderModel = std::make_shared<TerrainRenderModel>(TerrainRenderModel(terrainModel, terrainMaterial, terrainSpace, texturePack, terrainVaoId));

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

			// Create stall entity
			auto stallModel = std::make_shared<GeometryModel>(WavefrontObjParser::parseFile("D:/Blender Files/stall.obj"));
			auto stallMaterial = std::make_shared<Material>(MaterialLibraryParser::parseFile("D:/Blender Files/Cube.mtl"));
			stallMaterial->getLightingModel()->setReflectivity(1.0f);
			stallMaterial->getLightingModel()->setRefractiveIndex(1.33f);
			unsigned int stallModelId = Loader::loadGeometryModel(*stallModel);
			unsigned int stallTextureId = Loader::loadTexture("D:/Blender Files/stallTexture.png");
			auto stallRenderModel = std::make_shared<RenderModel>(RenderModel(stallModel, stallMaterial, stallModelId, stallTextureId, skyboxTextureId));
			auto stallSpaceModel = std::make_shared<SpaceModel>(SpaceModel(Vec3(0, 0, -10), Vec3(0, 180, 0), Vec3(1, 1, 1)));
			auto stallEntity = std::make_shared<Entity>(Entity(stallRenderModel, stallSpaceModel));

			// Create camera
			std::shared_ptr<Camera> camera = std::make_shared<Camera>(Camera(Vec3(0, 0.2f, 0.5f), Vec3(-0.2f, 0, 0)));
			renderEngine.loadCamera(camera);

			// Create light
			auto lightPosition = std::make_shared<Vec3>(Vec3(0, 0, 0));
			renderEngine.loadLight(lightPosition);

			// Load entity
			renderEngine.loadEntity(stallEntity);
			renderEngine.loadSkybox(skyboxRenderModel);
			renderEngine.loadTerrain(terrainRenderModel);
			
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);

			// Main loop
			while (!window.isClosed())
			{
				window.clear();

				renderEngine.render();
				stallSpaceModel->setRotation(stallSpaceModel->getRotation().add(Vec3(0, 0.5f, 0)));
				camera->setRotation(camera->getRotation().add(Vec3(0, 0.5f, 0)));

				window.update();
			}
		}
		catch (std::exception e)
		{
			SGE_ERROR("Unexpected error: " + std::string(e.what()));
		}

		system("PAUSE");
	}
}
