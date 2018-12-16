#include "sgepch.h"
#include "WaterShaderConstants.h"

namespace SimpleGameEngine::Shaders
{
	const std::string WaterShaderConstants::VERT_MODEL_MATRIX = "uModelMatrix";
	const std::string WaterShaderConstants::VERT_VIEW_MATRIX = "uViewMatrix";
	const std::string WaterShaderConstants::VERT_PROJECTION_MATRIX = "uProjectionMatrix";
	const std::string WaterShaderConstants::VERT_EYE_POSITION = "uEyePosition";
	const std::string WaterShaderConstants::VERT_SUN_POSITION = "uSunPosition";

	const std::string WaterShaderConstants::FRAG_WATER_REFLECTION_SAMPLER = "uWaterReflectionSampler";
	const std::string WaterShaderConstants::FRAG_WATER_REFRACTION_SAMPLER = "uWaterRefractionSampler";
	const std::string WaterShaderConstants::FRAG_WATER_DUDV_MAP_SAMPLER = "uWaterDuDvMapSampler";
	const std::string WaterShaderConstants::FRAG_WATER_FLOW_FACTOR = "uWaterFlowFactor";
	const std::string WaterShaderConstants::FRAG_FRESNEL_HIGHLIGHT = "uFresnelHighlight";
	const std::string WaterShaderConstants::FRAG_WATER_NORMAL_MAP_SAMPLER = "uWaterNormalMapSampler";
	const std::string WaterShaderConstants::FRAG_SUN_COLOR = "uSunColor";
	const std::string WaterShaderConstants::FRAG_DEPTH_MAP_SAMPLER = "uWaterDepthMapSampler";
	const std::string WaterShaderConstants::FRAG_NEAR_CLIPPING_PLANE = "uNearClippingPlane";
	const std::string WaterShaderConstants::FRAG_FAR_CLIPPING_PLANE = "uFarClippingPlane";
}
