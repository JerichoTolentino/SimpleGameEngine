#include "Application.h"
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

using namespace SimpleGameEngine::Cameras;
using namespace SimpleGameEngine::Display;
using namespace SimpleGameEngine::Parsers;
using namespace SimpleGameEngine::Loaders;
using namespace SimpleGameEngine::Renderers;
using namespace SimpleGameEngine::Models;
using namespace SimpleGameEngine::Shaders;
using namespace SimpleGameEngine::Math;

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
			Shader entityShader = ShaderLoader::loadShader(
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/src/SimpleGameEngine/Shaders/entityVertex.vert", 
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/src/SimpleGameEngine/Shaders/entityFragment.frag");
			Shader terrainShader = ShaderLoader::loadShader(
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/src/SimpleGameEngine/Shaders/terrainVertex.vert", 
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/src/SimpleGameEngine/Shaders/terrainFragment.frag");
			Shader skyboxShader = ShaderLoader::loadShader(
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/src/SimpleGameEngine/Shaders/skyboxVertex.vert", 
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/src/SimpleGameEngine/Shaders/skyboxFragment.frag");

			// Make renderers
			EntityRenderer entityRenderer(entityShader);
			TerrainRenderer terrainRenderer(terrainShader);
			SkyboxRenderer skyboxRenderer(skyboxShader);
			RenderEngine renderEngine(entityRenderer, terrainRenderer, skyboxRenderer);

			// Create stall entity
			GeometryModel stallModel = WavefrontObjParser::parseFile("D:/Blender Files/stall.obj");
			Material stallMaterial = MaterialLibraryParser::parseFile("D:/Blender Files/Cube.mtl");
			unsigned int stallModelId = Loader::loadGeometryModel(stallModel);
			unsigned int stallTextureId = Loader::loadTexture("D:/Blender Files/stallTexture.png");
			RenderModel stallRenderModel = RenderModel(stallModel, stallMaterial, stallModelId, stallTextureId);
			Entity stallEntity(stallRenderModel, SpaceModel(Vec3(0, 0, -10), Vec3(0, 0, 0), Vec3(1, 1, 1)));
			SGE_CORE_WARNING("Successfully loaded stall model.");

			// Create terrain
			TexturePack texturePack = Loader::loadTexturePack(
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/brickPath.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/broken_pavement.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/cobble.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/dirt.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/zombieBlendMap.png");
			SpaceModel terrainSpace(Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(1, 1, 1));
			HeightMap heightMap = Loader::loadHeightMap("C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/zombieHeightMap.png", 20);
			TerrainModel terrainModel(TerrainModel::GenerateTerrainMesh(10, 10, 10, heightMap), terrainSpace, heightMap, 10, 10, 10);
			TerrainRenderModel terrainRenderModel(terrainModel, stallMaterial, terrainSpace, texturePack);

			// Create skybox
			SkyboxModel skyboxModel = SkyboxModel::CreateSkyboxModel(5);
			GLuint skyboxVaoId = Loader::loadSkybox(skyboxModel);
			GLuint skyboxTextureId = Loader::loadCubemapTexture(
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/Lycksele3/posx.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/Lycksele3/negx.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/Lycksele3/posy.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/Lycksele3/negy.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/Lycksele3/posz.jpg",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/res/textures/Lycksele3/negz.jpg"
			);
			SkyboxRenderModel skyboxRenderModel(skyboxModel, skyboxVaoId, skyboxTextureId);

			// Create camera
			Camera camera(Vec3(0, 0, 5), Vec3(0, 0, 0));
			renderEngine.loadCamera(camera);

			// Create light
			Vec3 lightPosition(5, 10, -5);
			renderEngine.loadLight(lightPosition);

			// Load entity
			renderEngine.loadEntity(stallEntity);
			renderEngine.loadSkybox(skyboxRenderModel);
			renderEngine.loadTerrain(terrainRenderModel);

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);

			// Main loop
			while (true)
			{
				window.clear();

				renderEngine.render();

				window.update();
			}
			window.forceClose();
		}
		catch (std::exception e)
		{
			SGE_ERROR("Unexpected error: " + std::string(e.what()));
			system("PAUSE");
		}
	}
}
