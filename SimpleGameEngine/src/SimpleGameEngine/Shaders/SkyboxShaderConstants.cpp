#include "sgepch.h"
#include "SkyboxShaderConstants.h"

namespace SimpleGameEngine::Shaders
{
	const std::string SkyboxShaderConstants::VERT_PROJECTION_MATRIX = "uProjectionMatrix";
	const std::string SkyboxShaderConstants::VERT_VIEW_MATRIX = "uViewMatrix";

	const std::string SkyboxShaderConstants::FRAG_CUBEMAP_SAMPLER = "uCubemapSampler";
}
