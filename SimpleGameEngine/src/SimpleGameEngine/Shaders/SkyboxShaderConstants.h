#pragma once
#include <string>

namespace SimpleGameEngine::Shaders
{
	class SkyboxShaderConstants
	{
	public:
		static const std::string VERT_PROJECTION_MATRIX;
		static const std::string VERT_VIEW_MATRIX;

		static const std::string FRAG_CUBEMAP_SAMPLER;
	};
}
