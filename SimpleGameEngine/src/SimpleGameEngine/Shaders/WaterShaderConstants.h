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
		static const std::string VERT_SUN_POSITION;
		static const std::string VERT_TILE_FACTOR;

		static const std::string FRAG_WATER_REFLECTION_SAMPLER;
		static const std::string FRAG_WATER_REFRACTION_SAMPLER;
		static const std::string FRAG_WATER_DUDV_MAP_SAMPLER;
		static const std::string FRAG_WATER_FLOW_FACTOR;
		static const std::string FRAG_FRESNEL_CONSTANT;
		static const std::string FRAG_WATER_NORMAL_MAP_SAMPLER;
		static const std::string FRAG_SUN_COLOR;
		static const std::string FRAG_DEPTH_MAP_SAMPLER;
		static const std::string FRAG_NEAR_CLIPPING_PLANE;
		static const std::string FRAG_FAR_CLIPPING_PLANE;
		static const std::string FRAG_WAVE_STRENGTH;
		static const std::string FRAG_SHINE_DAMPER;
		static const std::string FRAG_REFLECTIVITY;
	};
}
