#include "sgepch.h"
#include "WaterShaderConstants.h"

namespace SimpleGameEngine::Shaders
{
	const std::string WaterShaderConstants::VERT_MODEL_MATRIX = "uModelMatrix";
	const std::string WaterShaderConstants::VERT_VIEW_MATRIX = "uViewMatrix";
	const std::string WaterShaderConstants::VERT_PROJECTION_MATRIX = "uProjectionMatrix";

	const std::string WaterShaderConstants::FRAG_WATER_REFLECTION_SAMPLER = "uWaterReflectionSampler";
	const std::string WaterShaderConstants::FRAG_WATER_REFRACTION_SAMPLER = "uWaterRefractionSampler";
	const std::string WaterShaderConstants::FRAG_WATER_DUDV_MAP_SAMPLER = "uWaterDuDvMapSampler";
	const std::string WaterShaderConstants::FRAG_WATER_FLOW_FACTOR = "uWaterFlowFactor";
}
