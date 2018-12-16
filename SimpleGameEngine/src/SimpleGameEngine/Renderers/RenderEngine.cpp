#include "sgepch.h"
#include "RenderEngine.h"

#include "../Loaders/Loader.h"
#include "../Loaders/FboLoader.h"
#include "../Logic/ModelTransformer.h"

using namespace SimpleGameEngine::Math;
using namespace SimpleGameEngine::Models;
using namespace SimpleGameEngine::Cameras;
using namespace SimpleGameEngine::Loaders;
using namespace SimpleGameEngine::Logic;

namespace SimpleGameEngine::Renderers
{
	const int RenderEngine::MAIN_FBO_WIDTH = 1280;
	const int RenderEngine::MAIN_FBO_HEIGHT = 720;
	const int RenderEngine::REFLECTION_FBO_WIDTH = 1280;
	const int RenderEngine::REFLECTION_FBO_HEIGHT= 720;
	const int RenderEngine::REFRACTION_FBO_WIDTH= 1280;
	const int RenderEngine::REFRACTION_FBO_HEIGHT= 720;
	const std::string RenderEngine::WATER_DUDV_MAP_TEXTURE = "C:\\GitHubRepositories\\SimpleGameEngine\\SimpleGameEngine\\res\\textures\\waterDuDvMap.png";
	const std::string RenderEngine::WATER_NORMAL_MAP_TEXTURE = "C:\\GitHubRepositories\\SimpleGameEngine\\SimpleGameEngine\\res\\textures\\waterNormalMap.png";



	RenderEngine::RenderEngine()
	{
	}

	RenderEngine::RenderEngine(
		const std::shared_ptr<EntityRenderer> entityRenderer,
		const std::shared_ptr<TerrainRenderer> terrainRenderer,
		const std::shared_ptr<SkyboxRenderer> skyboxRenderer,
		const std::shared_ptr<WaterRenderer> waterRenderer,
		const std::shared_ptr<GuiRenderer> guiRenderer)
		:
		m_entityRenderer(entityRenderer),
		m_terrainRenderer(terrainRenderer),
		m_skyboxRenderer(skyboxRenderer),
		m_waterRenderer(waterRenderer),
		m_guiRenderer(guiRenderer)
	{
		// Initialize default FBO
		m_mainFbo = std::make_shared<OpenGL::FrameBufferObject>(0, MAIN_FBO_WIDTH, MAIN_FBO_HEIGHT);

		// Initialize water FBOs
		m_waterReflectionFbo = std::make_shared<OpenGL::WaterReflectionFbo>(FboLoader::CreateWaterReflectionFbo(REFLECTION_FBO_WIDTH, REFLECTION_FBO_HEIGHT));
		m_waterRefractionFbo = std::make_shared<OpenGL::WaterRefractionFbo>(FboLoader::CreateWaterRefractionFbo(REFRACTION_FBO_WIDTH, REFRACTION_FBO_HEIGHT));

		// Load in water FBO textures
		m_waterRenderer->loadWaterReflectionFbo(m_waterReflectionFbo);
		m_waterRenderer->loadWaterRefractionFbo(m_waterRefractionFbo);

		// Load in water dudv map
		unsigned int dudvMapTextureId = Loader::loadTexture(WATER_DUDV_MAP_TEXTURE);
		m_waterRenderer->loadWaterDuDvMap(dudvMapTextureId);

		// Load in fresnel constant
		m_waterRenderer->loadFresnelHighlight(0.5f);

		// Load in water normal map
		unsigned int normalMapId = Loader::loadTexture(WATER_NORMAL_MAP_TEXTURE);
		m_waterRenderer->loadWaterNormalMap(normalMapId);

		// Load in depth map
		m_waterRenderer->loadWaterDepthMap(m_waterRefractionFbo->getDepthTextureId());

		m_waterHeight = 0;
	}

	RenderEngine::RenderEngine(const RenderEngine & other)
		: RenderEngine(other.m_entityRenderer, other.m_terrainRenderer, other.m_skyboxRenderer, other.m_waterRenderer, other.m_guiRenderer)
	{
	}

	RenderEngine::~RenderEngine()
	{
	}



	std::shared_ptr<EntityRenderer> RenderEngine::getEntityRenderer() const
	{
		return m_entityRenderer;
	}

	std::shared_ptr<TerrainRenderer> RenderEngine::getTerrainRenderer() const
	{
		return m_terrainRenderer;
	}

	std::shared_ptr<SkyboxRenderer> RenderEngine::getSkyboxRenderer() const
	{
		return m_skyboxRenderer;
	}

	std::shared_ptr<WaterRenderer> RenderEngine::getWaterRenderer() const
	{
		return m_waterRenderer;
	}

	std::shared_ptr<GuiRenderer> RenderEngine::getGuiRenderer() const
	{
		return m_guiRenderer;
	}

	std::shared_ptr<OpenGL::FrameBufferObject> RenderEngine::getMainFbo() const
	{
		return m_mainFbo;
	}

	std::shared_ptr<OpenGL::WaterReflectionFbo> RenderEngine::getWaterReflectionFbo() const
	{
		return m_waterReflectionFbo;
	}

	std::shared_ptr<OpenGL::WaterRefractionFbo> RenderEngine::getWaterRefractionFbo() const
	{
		return m_waterRefractionFbo;
	}

	void RenderEngine::setWaterHeight(float height)
	{
		m_waterHeight = height;
	}

	void RenderEngine::loadScene(const RenderScene & scene)
	{
		m_scene = scene;

		// Load projection matrix
		Mat4 projectionMatrix = *scene.getProjectionMatrix();
		m_entityRenderer->loadProjectionMatrix(projectionMatrix);
		m_terrainRenderer->loadProjectionMatrix(projectionMatrix);
		m_skyboxRenderer->loadProjectionMatrix(projectionMatrix);
		m_waterRenderer->loadProjectionMatrix(projectionMatrix);
	}

	void RenderEngine::loadGuiRenderElements(const std::vector<std::shared_ptr<Models::GuiRenderElement>>& guiRenderElements)
	{
		for (auto guiRenderElement : guiRenderElements)
		{
			m_guiRenderElements.push_back(guiRenderElement);
		}
	}

	void RenderEngine::render() const
	{
		Camera camera = *m_scene.getCamera();
		auto lights = *m_scene.getLights();
		auto skybox = m_scene.getSkybox();

		glEnable(GL_CLIP_DISTANCE0);

		// Transform camera for reflection texture
		float distance = std::sqrtf(std::powf(camera.getPosition().y - m_waterHeight, 2)) * 2;
		camera.setPosition(Vec3(camera.getPosition().x, camera.getPosition().y - distance, camera.getPosition().z));
		camera.setRotation(Vec3(-camera.getRotation().x, camera.getRotation().y, camera.getRotation().z));

		// Render to water reflection FBO
		FboLoader::BindFrameBuffer(*m_waterReflectionFbo);
		m_entityRenderer->loadClippingPlane(Vec4(0, 1, 0, -m_waterHeight + 1));		// Add slight offset to remove artifacts at water edge
		m_terrainRenderer->loadClippingPlane(Vec4(0, 1, 0, -m_waterHeight + 1));	// Add slight offset to remove artifacts at water edge
		renderEntities(camera, lights);
		renderTerrains(camera, lights);
		if (skybox != nullptr)
		{
			renderSkybox(camera, *skybox);
		}

		// Transform camera back to original position
		camera.setPosition(Vec3(camera.getPosition().x, camera.getPosition().y + distance, camera.getPosition().z));
		camera.setRotation(Vec3(-camera.getRotation().x, camera.getRotation().y, camera.getRotation().z));

		// Render to water refraction FBO
		FboLoader::BindFrameBuffer(*m_waterRefractionFbo);
		m_entityRenderer->loadClippingPlane(Vec4(0, -1, 0, m_waterHeight));
		m_terrainRenderer->loadClippingPlane(Vec4(0, -1, 0, m_waterHeight));
		renderEntities(camera, lights);
		renderTerrains(camera, lights);
		if (skybox != nullptr)
		{
			renderSkybox(camera, *skybox);
		}

		glDisable(GL_CLIP_DISTANCE0);		

		// Render to main FBO
		FboLoader::BindFrameBuffer(*m_mainFbo);
		renderEntities(camera, lights);
		renderTerrains(camera, lights);
		if (skybox != nullptr)
		{
			renderSkybox(camera, *skybox);
		}
		renderWater(camera, lights);
		renderGui();
	}



	RenderEngine & RenderEngine::operator=(const RenderEngine & other)
	{
		m_entityRenderer = other.m_entityRenderer;
		m_terrainRenderer = other.m_terrainRenderer;
		m_skyboxRenderer = other.m_skyboxRenderer;
		m_waterRenderer = other.m_waterRenderer;
		m_guiRenderer = other.m_guiRenderer;

		return *this;
	}



	void RenderEngine::onWindowResized(Events::WindowResizeEvent & e)
	{
		m_mainFbo->setWidth(e.getWidth());
		m_mainFbo->setHeight(e.getHeight());
	}



	void RenderEngine::renderEntities(const Cameras::Camera & camera, const std::vector<std::shared_ptr<Models::LightSource>> & lights) const
	{
		for (const auto & entityBatch : *m_scene.getEntityBatches())
		{
			auto entities = entityBatch.second;

			m_entityRenderer->loadRenderModel(*entities.at(0)->getRenderModel());

			for (const auto entity : entities)
			{
				m_entityRenderer->loadCamera(camera);
				m_entityRenderer->loadLights(lights);
				m_entityRenderer->loadEntity(*entity);
				m_entityRenderer->render(*entity);
			}

			m_entityRenderer->unloadRenderModel();
		}
	}

	void RenderEngine::renderTerrains(const Cameras::Camera & camera, const std::vector<std::shared_ptr<Models::LightSource>> & lights) const
	{
		for (const auto & terrainBatch : *m_scene.getTerrainBatches())
		{
			auto terrains = terrainBatch.second;
			for (const auto terrain : terrains)
			{
				m_terrainRenderer->loadCamera(camera);
				m_terrainRenderer->loadLights(lights);
				m_terrainRenderer->loadTerrain(*terrain);
				m_terrainRenderer->render(*terrain);
				m_terrainRenderer->unloadTerrain();
			}
		}
	}
	
	void RenderEngine::renderSkybox(const Cameras::Camera & camera, const Models::SkyboxRenderModel & skybox) const
	{
		m_skyboxRenderer->loadCamera(camera);
		m_skyboxRenderer->loadSkybox(skybox);
		m_skyboxRenderer->render(skybox);
		m_skyboxRenderer->unloadSkybox();
	}
	
	void RenderEngine::renderWater(const Cameras::Camera & camera, const std::vector<std::shared_ptr<Models::LightSource>> & lights) const
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_CULL_FACE);
		for (const auto & waterBatch : *m_scene.getWaterBatches())
		{
			auto waters = waterBatch.second;

			m_waterRenderer->loadWaterRenderModel(*waters.at(0)->getWaterRenderModel());

			for (const auto water : waters)
			{
				m_waterRenderer->loadSun(*lights.at(0));
				m_waterRenderer->loadCamera(camera);
				m_waterRenderer->loadLights(lights);
				m_waterRenderer->loadWaterEntity(*water);
				m_waterRenderer->updateWaterFlow();
				m_waterRenderer->render(*water);
			}

			m_waterRenderer->unloadWaterRenderModel();
		}
		glEnable(GL_CULL_FACE);
		glDisable(GL_BLEND);
	}
	
	void RenderEngine::renderGui() const
	{
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		for (const auto & guiRenderElement : m_guiRenderElements)
		{
			m_guiRenderer->loadGuiRenderElement(*guiRenderElement);
			m_guiRenderer->render(*guiRenderElement);
			m_guiRenderer->unloadGuiRenderElement();
		}
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}
}