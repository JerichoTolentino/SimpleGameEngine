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



	RenderEngine::RenderEngine()
	{
	}

	RenderEngine::RenderEngine(
		const std::shared_ptr<OpenGL::FrameBufferObject> mainFbo,
		const std::shared_ptr<OpenGL::WaterReflectionFbo> waterReflectionFbo,
		const std::shared_ptr<OpenGL::WaterRefractionFbo> waterRefractionFbo,
		const std::shared_ptr<OpenGL::ShadowMapFbo> shadowMapFbo,
		const std::shared_ptr<Projection::OrthoProjectionBox> shadowBox,
		const std::shared_ptr<EntityRenderer> entityRenderer,
		const std::shared_ptr<TerrainRenderer> terrainRenderer,
		const std::shared_ptr<SkyboxRenderer> skyboxRenderer,
		const std::shared_ptr<WaterRenderer> waterRenderer,
		const std::shared_ptr<GuiRenderer> guiRenderer,
		const std::shared_ptr<EntityShadowRenderer> entityShadowRenderer)
		:
		m_mainFbo(mainFbo),
		m_waterReflectionFbo(waterReflectionFbo),
		m_waterRefractionFbo(waterRefractionFbo),
		m_shadowMapFbo(shadowMapFbo),
		m_shadowBox(shadowBox),
		m_entityRenderer(entityRenderer),
		m_terrainRenderer(terrainRenderer),
		m_skyboxRenderer(skyboxRenderer),
		m_waterRenderer(waterRenderer),
		m_guiRenderer(guiRenderer),
		m_entityShadowRenderer(entityShadowRenderer)
	{
		m_waterHeight = 0;

		// TODO: REMOVE
		auto guiQuad = std::make_shared<GuiGeometry>(GuiGeometry::GenerateQuad());
		auto guiQuadVao = Loader::loadGuiElement(*guiQuad);
		auto guiRenderElement = std::make_shared<GuiRenderElement>
			(
				guiQuad,
				guiQuadVao,
				m_shadowMapFbo->getDepthTextureId(),
				Vec2(0.75, 0.75),
				0,
				Vec2(0.25, 0.25)
			);
		m_guiRenderElements.push_back(guiRenderElement);

		auto guiRenderElement2 = std::make_shared<GuiRenderElement>
			(
				guiQuad,
				guiQuadVao,
				m_waterReflectionFbo->getTextureId(),
				Vec2(-0.75, 0.75),
				0,
				Vec2(0.25, 0.25)
			);
		m_guiRenderElements.push_back(guiRenderElement2);

		auto guiRenderElement3 = std::make_shared<GuiRenderElement>
			(
				guiQuad,
				guiQuadVao,
				m_waterRefractionFbo->getTextureId(),
				Vec2(0, 0.75),
				0,
				Vec2(0.25, 0.25)
			);
		m_guiRenderElements.push_back(guiRenderElement3);
	}

	RenderEngine::RenderEngine(const RenderEngine & other)
		: RenderEngine(other.m_mainFbo, 
					   other.m_waterReflectionFbo, 
					   other.m_waterRefractionFbo, 
					   other.m_shadowMapFbo,
					   other.m_shadowBox,
					   other.m_entityRenderer, 
					   other.m_terrainRenderer, 
					   other.m_skyboxRenderer, 
					   other.m_waterRenderer, 
					   other.m_guiRenderer,
					   other.m_entityShadowRenderer)
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

	std::shared_ptr<EntityShadowRenderer> RenderEngine::getEntityShadowRenderer() const
	{
		return m_entityShadowRenderer;
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
		m_waterReflectionFbo->bind();
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
		m_waterRefractionFbo->bind();
		m_entityRenderer->loadClippingPlane(Vec4(0, -1, 0, m_waterHeight));
		m_terrainRenderer->loadClippingPlane(Vec4(0, -1, 0, m_waterHeight));
		renderEntities(camera, lights);
		renderTerrains(camera, lights);
		if (skybox != nullptr)
		{
			renderSkybox(camera, *skybox);
		}

		glDisable(GL_CLIP_DISTANCE0);		

		// Render to shadow buffer
		m_shadowMapFbo->bind();
		renderEntityShadows(camera, *lights.at(0), *m_shadowBox);

		// Render to main FBO
		m_mainFbo->bind();
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
		m_mainFbo = other.m_mainFbo;
		m_waterReflectionFbo = other.m_waterReflectionFbo;
		m_waterRefractionFbo = other.m_waterRefractionFbo;
		m_shadowMapFbo = other.m_shadowMapFbo;
		m_shadowBox = other.m_shadowBox;
		m_entityRenderer = other.m_entityRenderer;
		m_terrainRenderer = other.m_terrainRenderer;
		m_skyboxRenderer = other.m_skyboxRenderer;
		m_waterRenderer = other.m_waterRenderer;
		m_guiRenderer = other.m_guiRenderer;
		m_entityShadowRenderer = other.m_entityShadowRenderer;

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
				// Update water flow
				water->updateFlowFactor(1);

				m_waterRenderer->loadSun(*lights.at(0));
				m_waterRenderer->loadCamera(camera);
				m_waterRenderer->loadLights(lights);
				m_waterRenderer->loadWaterEntity(*water);
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

	void RenderEngine::renderEntityShadows(const Cameras::Camera & camera, const Models::LightSource & sun, Projection::OrthoProjectionBox & shadowBox) const
	{
		// Calculate projection matrix
		//Mat4 projectionMatrix = *m_scene.getProjectionMatrix();
		Mat4 projectionMatrix = Mat4::GenerateOrthographicProjectionMatrix(10, 10, 20);

		// Calculate view matrix
		//Mat4 lightViewMatrix = camera.generateViewMatrix();
		Mat4 lightViewMatrix = Mat4::GenerateViewMatrix(Vec3(0, 0, 0), Vec3(0, 0, 0));

		// Calculate light view-projection matrix
		Mat4 lightViewProjectionMatrix = lightViewMatrix * projectionMatrix;

		// Update shadow box
		//shadowBox.update(lightViewMatrix, camera.getPosition(), camera.getRotation());

		m_entityShadowRenderer->loadTextureUnits();
		for (const auto & entityBatch : *m_scene.getEntityBatches())
		{
			auto entities = entityBatch.second;

			m_entityShadowRenderer->loadRenderModel(*entities.at(0)->getRenderModel());

			for (const auto entity : entities)
			{
				// Calculate model-view-projection matrix
				SpaceModel spaceModel = *entity->getSpaceModel();
				Mat4 entityTransform;
				entityTransform.setIdentity();
				entityTransform.transform(spaceModel.getPosition(), spaceModel.getRotation(), spaceModel.getScale());

				Mat4 mvpMatrix = entityTransform * lightViewProjectionMatrix;

				m_entityShadowRenderer->loadModelViewProjectionMatrix(mvpMatrix);
				m_entityShadowRenderer->loadModelMatrix(entityTransform);
				m_entityShadowRenderer->loadViewMatrix(lightViewMatrix);
				m_entityShadowRenderer->loadProjectionMatrix(projectionMatrix);
				m_entityShadowRenderer->render(*entity);
			}

			m_entityShadowRenderer->unloadRenderModel();
		}
	}
}