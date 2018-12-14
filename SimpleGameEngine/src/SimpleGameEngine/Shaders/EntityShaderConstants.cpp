#include "sgepch.h"
#include "EntityShaderConstants.h"

namespace SimpleGameEngine::Shaders
{
	const std::string EntityShaderConstants::VERT_MODEL_MATRIX = "uModelMatrix";
	const std::string EntityShaderConstants::VERT_PROJECTION_MATRIX = "uProjectionMatrix";
	const std::string EntityShaderConstants::VERT_VIEW_MATRIX = "uViewMatrix";
	const std::string EntityShaderConstants::VERT_NORMAL_MATRIX = "uNormalMatrix";
	const std::string EntityShaderConstants::VERT_LIGHT_POSITIONS = "uLightPositions";
	const std::string EntityShaderConstants::VERT_EYE_POSITION = "uEyePosition";

	const std::string EntityShaderConstants::VERT_CLIPPING_PLANE = "uClippingPlane";

	const std::string EntityShaderConstants::FRAG_AMBIENT = "uAmbient";
	const std::string EntityShaderConstants::FRAG_EMISSIVE = "uEmissive";
	const std::string EntityShaderConstants::FRAG_DIFFUSE = "uDiffuse";
	const std::string EntityShaderConstants::FRAG_SPECULAR = "uSpecular";
	const std::string EntityShaderConstants::FRAG_SPECULAR_HIGHLIGHT = "uSpecularHighlight";
	const std::string EntityShaderConstants::FRAG_REFLECTIVITY = "uReflectivity";
	const std::string EntityShaderConstants::FRAG_REFRACTIVE_INDEX = "uRefractiveIndex";
	const std::string EntityShaderConstants::FRAG_OPACITY = "uOpacity";
	const std::string EntityShaderConstants::FRAG_LIGHT_COLORS = "uLightColors";
	const std::string EntityShaderConstants::FRAG_LIGHT_ATTENUATIONS = "uLightAttenuations";

	const std::string EntityShaderConstants::FRAG_TEXTURE_SAMPLER = "uTextureSampler";
	const std::string EntityShaderConstants::FRAG_CUBEMAP_SAMPLER = "uCubemapSampler";

	const int EntityShaderConstants::MAX_LIGHTS = 5;
}