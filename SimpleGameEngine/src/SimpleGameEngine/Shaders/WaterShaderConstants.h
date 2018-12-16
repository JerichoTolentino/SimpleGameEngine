#pragma once

namespace SimpleGameEngine::Shaders
{
	class WaterShaderConstants
	{
	public:
		static const std::string VERT_MODEL_MATRIX;
		static const std::string VERT_VIEW_MATRIX;
		static const std::string VERT_PROJECTION_MATRIX;
		static const std::string VERT_EYE_POSITION;

		static const std::string FRAG_WATER_REFLECTION_SAMPLER;
		static const std::string FRAG_WATER_REFRACTION_SAMPLER;
		static const std::string FRAG_WATER_DUDV_MAP_SAMPLER;
		static const std::string FRAG_WATER_FLOW_FACTOR;
		static const std::string FRAG_FRESNEL_HIGHLIGHT;
	};
}
