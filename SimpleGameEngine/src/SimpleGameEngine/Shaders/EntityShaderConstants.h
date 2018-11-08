#pragma once
#include <string>

namespace SimpleGameEngine::Shaders
{
	class EntityShaderConstants
	{
	public:
		static const std::string VERT_MODEL_MATRIX;
		static const std::string VERT_PROJECTION_MATRIX;
		static const std::string VERT_VIEW_MATRIX;
		static const std::string VERT_NORMAL_MATRIX;
		static const std::string VERT_LIGHT_POSITION;
		static const std::string VERT_EYE_POSITION;

		static const std::string FRAG_AMBIENT;
		static const std::string FRAG_EMISSIVE;
		static const std::string FRAG_DIFFUSE;
		static const std::string FRAG_SPECULAR;
		static const std::string FRAG_SPECULAR_HIGHLIGHT;
		static const std::string FRAG_REFLECTIVITY;
		static const std::string FRAG_REFRACTIVE_INDEX;
		static const std::string FRAG_OPACITY;
	};
}