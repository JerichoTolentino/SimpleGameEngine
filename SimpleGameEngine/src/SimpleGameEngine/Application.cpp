#include "sgepch.h"
#include "Application.h"
#include <memory>
#include "Display/Window.h"
#include "Parsers/WavefrontObjParser.h"
#include "Parsers/MaterialLibraryParser.h"
#include "Parsers/ParseException.h"
#include "Loaders/Loader.h"
#include "Loaders/FboLoader.h"
#include "Loaders/ShaderLoader.h"
#include "Models/RenderModel.h"
#include "Renderers/RenderEngine.h"
#include "OpenGL/WaterReflectionFbo.h"
#include "OpenGL/WaterRefractionFbo.h"
#include "OpenGL/ShadowMapFbo.h"
#include "Shaders/Shader.h"
#include "Models/TerrainRenderModel.h"
#include "Models/SkyboxRenderModel.h"
#include "Models/HeightMap.h"
#include "Models/LightSource.h"
#include "Math/Vec3.h"
#include "Log.h"
#include "Logic/ModelTransformer.h"
#include "Projection/OrthoProjectionBox.h"

using namespace SimpleGameEngine::Cameras;
using namespace SimpleGameEngine::Display;
using namespace SimpleGameEngine::Parsers;
using namespace SimpleGameEngine::Loaders;
using namespace SimpleGameEngine::Renderers;
using namespace SimpleGameEngine::Models;
using namespace SimpleGameEngine::Shaders;
using namespace SimpleGameEngine::Math;
using namespace SimpleGameEngine::Logic;
using namespace SimpleGameEngine::OpenGL;

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
			Window window(1280, 720);

			// Build scene
			RenderScene scene;

			// Load projection matrix
			int windowWidth, windowHeight;
			window.getWindowSize(windowWidth, windowHeight);
			float aspectRatio = windowHeight == 0 ? 1 : (float) windowWidth / windowHeight;
			float nearPlane = 0.1f;
			float farPlane = 1000.0f;
			float fov = 70;
			auto projectionMatrix = std::make_shared<Mat4>(Mat4::GeneratePerspectiveProjectionMatrix(aspectRatio, fov, nearPlane, farPlane));
			scene.setProjectionMatrix(projectionMatrix);

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
			auto waterShader = std::make_shared<Shader>(ShaderLoader::loadShader(
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/src/SimpleGameEngine/Shaders/waterVertex.vert",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/src/SimpleGameEngine/Shaders/waterFragment.frag"));
			auto guiShader = std::make_shared<Shader>(ShaderLoader::loadShader(
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/src/SimpleGameEngine/Shaders/guiVertex.vert",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/src/SimpleGameEngine/Shaders/guiFragment.frag"
			));
			auto entityShadowShader = std::make_shared<Shader>(ShaderLoader::loadShader(
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/src/SimpleGameEngine/Shaders/shadowVertex.vert",
				"C:/GitHubRepositories/SimpleGameEngine/SimpleGameEngine/src/SimpleGameEngine/Shaders/shadowFragment.frag"
			));

			// Make FBOs
			auto mainFbo = std::make_shared<FrameBufferObject>(0, windowWidth, windowHeight);
			auto waterReflectionFbo = std::make_shared<WaterReflectionFbo>(FboLoader::CreateWaterReflectionFbo(windowWidth, windowHeight));
			auto waterRefractionFbo = std::make_shared<WaterRefractionFbo>(FboLoader::CreateWaterRefractionFbo(windowWidth, windowHeight));
			//auto shadowFbo = std::make_shared<ShadowMapFbo>(FboLoader::CreateShadowMapFbo(2048, 2048));
			auto shadowFbo = std::make_shared<ShadowMapFbo>(FboLoader::CreateShadowMapFbo(windowWidth, windowHeight));

			// Make shadow box
			auto shadowBox = std::make_shared<Projection::OrthoProjectionBox>(Projection::OrthoProjectionBox::GenerateOrthoProjectionBox(fov, nearPlane, aspectRatio));

			// Make renderers
			auto entityRenderer = std::make_shared<EntityRenderer>(EntityRenderer(entityShader));
			auto terrainRenderer = std::make_shared<TerrainRenderer>(TerrainRenderer(terrainShader));
			auto skyboxRenderer = std::make_shared<SkyboxRenderer>(SkyboxRenderer(skyboxShader));
			auto waterRenderer = std::make_shared<WaterRenderer>(WaterRenderer(waterShader, waterReflectionFbo->getTextureId(), waterRefractionFbo->getTextureId(), waterRefractionFbo->getDepthTextureId()));
			auto guiRenderer = std::make_shared<GuiRenderer>(GuiRenderer(guiShader));
			auto entityShadowRenderer = std::make_shared<EntityShadowRenderer>(EntityShadowRenderer(entityShadowShader));
			RenderEngine renderEngine(mainFbo, waterReflectionFbo, waterRefractionFbo, shadowFbo, shadowBox, entityRenderer, terrainRenderer, skyboxRenderer, waterRenderer, guiRenderer, entityShadowRenderer);

			waterRenderer->loadClippingPlanes(nearPlane, farPlane);

#pragma region SceneGeneration

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

			auto stallRenderModel2 = std::make_shared<RenderModel>(RenderModel(*stallRenderModel));
			auto stallSpaceModel2 = std::make_shared<SpaceModel>(SpaceModel(Vec3(0, -3, 10), Vec3(0, 0, 0), Vec3(1, 1, 1)));
			auto stallEntity2 = std::make_shared<Entity>(Entity(stallRenderModel2, stallSpaceModel2));
			scene.addEntity(stallEntity2);

			// Create ugly water bottle entity
			auto waterBottleModel = std::make_shared<GeometryModel>(WavefrontObjParser::parseFile("D:/Blender Files/UglyWaterBottle.obj"));
			auto waterBottleMaterial = std::make_shared<Material>(std::make_shared<LightingModel>(LightingModel(0, 1, 0.1f, 0, 1.0f, 0.4f, 32, 1.5f)));
			unsigned int waterBottleModelId = Loader::loadGeometryModel(*waterBottleModel);
			unsigned int waterBottleTextureId = Loader::loadTexture("D:/Blender Files/WaterBottleTexture.png");
			auto waterBottleRenderModel = std::make_shared<RenderModel>(RenderModel(waterBottleModel, waterBottleMaterial, waterBottleModelId, waterBottleTextureId, skyboxTextureId));
			auto waterBottleSpaceModel = std::make_shared<SpaceModel>(SpaceModel(Vec3(-5, -3, -10), Vec3(0, 0, 0), Vec3(1, 1, 1)));
			auto waterBottleEntity = std::make_shared<Entity>(Entity(waterBottleRenderModel, waterBottleSpaceModel));
			scene.addEntity(waterBottleEntity);

			// Create second ugly water bottle entity
			auto waterBottleRenderModel2 = std::make_shared<RenderModel>(RenderModel(*waterBottleRenderModel));
			auto waterBottleSpaceModel2 = std::make_shared<SpaceModel>(SpaceModel(Vec3(0, -3, -10), Vec3(0, 0, 0), Vec3(1, 1, 1)));
			auto waterBottleEntity2 = std::make_shared<Entity>(Entity(waterBottleRenderModel2, waterBottleSpaceModel2));
			scene.addEntity(waterBottleEntity2);

			// Create water
			auto waterModel = std::make_shared<WaterModel>(WaterModel::GenerateWaterModel());
			auto dudvMapTextureId = Loader::loadTexture("C:\\GitHubRepositories\\SimpleGameEngine\\SimpleGameEngine\\res\\textures\\waterDuDvMap.png");
			auto normalMapTextureId = Loader::loadTexture("C:\\GitHubRepositories\\SimpleGameEngine\\SimpleGameEngine\\res\\textures\\waterNormalMap.png");
			auto waterRenderModel = std::make_shared<WaterRenderModel>(WaterRenderModel(waterModel,	Loader::loadWaterModel(*waterModel), dudvMapTextureId, normalMapTextureId));
			auto waterSpaceModel = std::make_shared<SpaceModel>(SpaceModel(Vec3(0, -14, 0), Vec3(0, 0, 0), Vec3(200, 1, 200)));
			auto waterProperties = std::make_shared<WaterProperties>(WaterProperties(0.5, 20, 0.5, 0.0003f, 0.2, 4.0));
			auto waterEntity = std::make_shared<WaterEntity>(WaterEntity(waterRenderModel, waterSpaceModel, waterProperties));
			scene.addWater(waterEntity);
			renderEngine.setWaterHeight(waterEntity->getSpaceModel()->getPosition().y);

			// Create camera
			std::shared_ptr<Camera> camera = std::make_shared<Camera>(Camera(Vec3(0, 0.2f, 0), Vec3(-0.2f, 0, 0)));
			camera->setDistanceFromEntity(100.0f);
			scene.setCamera(camera);

			// Create lights
			auto lightSources = std::vector<std::shared_ptr<Models::LightSource>>();
			auto testLight = std::make_shared<LightSource>(LightSource(Vec3(0, 15, -25), Vec3(1, 0, 0), Vec3(1, 0.01f, 0.002f)));
			auto testLight2 = std::make_shared<LightSource>(LightSource(Vec3(0, 0.2f, 0), Vec3(0, 0, 1), Vec3(1, 0.01f, 0.002f)));
			
			// THIS IS THE SUN (currently assumed at position 0 in water renderer and shadow renderer)
			lightSources.push_back(std::make_shared<LightSource>(LightSource(Vec3(-100000, 100000, -100000), Vec3(1, 1, 1))));


			lightSources.push_back(testLight);
			lightSources.push_back(testLight2);
			lightSources.push_back(std::make_shared<LightSource>(LightSource(Vec3(5, 2, -10), Vec3(0, 0, 1), Vec3(1, 0.01f, 0.002f))));
			lightSources.push_back(std::make_shared<LightSource>(LightSource(Vec3(-50, 2, -100), Vec3(0, 1, 0), Vec3(1, 0.01f, 0.002f))));
			for (auto light : lightSources)
			{
				scene.addLight(light);
			}
			

			// Add GUI elements
			auto guiQuad = std::make_shared<GuiGeometry>(GuiGeometry::GenerateQuad());
			unsigned int guiQuadVaoId = Loader::loadGuiElement(*guiQuad);
			std::vector<std::shared_ptr<GuiRenderElement>> guiRenderElements;
			guiRenderElements.push_back(std::make_shared<GuiRenderElement>(GuiRenderElement(
																			guiQuad,
																			guiQuadVaoId,
																			Loader::loadTexture("D:/Blender Files/transparent.png"),
																			Vec2(0.75, -0.75), 
																			0, 
																			Vec2(0.25f, 0.25f))));

#pragma endregion

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);

			renderEngine.loadGuiRenderElements(guiRenderElements);
			renderEngine.loadScene(scene);

			window.addWindowEventListener(&renderEngine);


			bool goLeft = false;
			bool goBack = true;
			bool goTerrainLeft = true;

			// Main loop
			while (!window.isClosed())
			{
				window.clear();

				renderEngine.render();

				//camera->follow(*stallSpaceModel);
				//camera->rotateAround(0.5f, 1);
				camera->setRotation(camera->getRotation() + Vec3(0, 0.5f, 0));

				ModelTransformer::rotate(*waterBottleSpaceModel, Vec3(0, 0.5f, 0));
				ModelTransformer::rotate(*stallSpaceModel, Vec3(0, 0.5f, 0));

				if (testLight->getPosition().x < -50)
					goLeft = false;
				else if (testLight->getPosition().x > 50)
					goLeft = true;
				
				if (goLeft)
				{
					testLight->translate(Vec3(-1, 0, 0));
				}
				else
				{
					testLight->translate(Vec3(1, 0, 0));
				}
				
				if (stallSpaceModel->getPosition().z < -50)
					goBack = false;
				else if (stallSpaceModel->getPosition().z > -10)
					goBack = true;
				
				if (goBack)
					ModelTransformer::translate(*stallSpaceModel, Vec3(0, 0, -0.2f));
				else
					ModelTransformer::translate(*stallSpaceModel, Vec3(0, 0, 0.2f));

				if (terrainSpace->getRotation().y > 45)
					goTerrainLeft = false;
				else if (terrainSpace->getRotation().y < -45)
					goTerrainLeft = true;

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
