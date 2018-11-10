#pragma once
#include <string>
#include <GL/glew.h>

namespace SimpleGameEngine::Shaders
{
	class TerrainShaderConstants
	{
	public:
		static const std::string VERT_MODEL_MATRIX;
		static const std::string VERT_PROJECTION_MATRIX;
		static const std::string VERT_VIEW_MATRIX;
		static const std::string VERT_LIGHT_POSITION;

		static const std::string FRAG_AMBIENT;
		static const std::string FRAG_DIFFUSE;
		static const std::string FRAG_OPACITY;
		static const std::string FRAG_TILE_FACTOR;
		static const std::string FRAG_BLEND_SAMPLER;
		static const std::string FRAG_RED_SAMPLER;
		static const std::string FRAG_GREEN_SAMPLER;
		static const std::string FRAG_BLUE_SAMPLER;
		static const std::string FRAG_BACKGROUND_SAMPLER;

		static const int BLEND_MAP_TEXTURE_SLOT;
		static const int RED_TEXTURE_SLOT;
		static const int GREEN_TEXTURE_SLOT;
		static const int BLUE_TEXTURE_SLOT;
		static const int BACKGROUND_TEXTURE_SLOT;

		static const GLenum BLEND_MAP_TEXTURE_SLOT_OPENGL;
		static const GLenum RED_TEXTURE_SLOT_OPENGL;
		static const GLenum GREEN_TEXTURE_SLOT_OPENGL;
		static const GLenum BLUE_TEXTURE_SLOT_OPENGL;
		static const GLenum BACKGROUND_TEXTURE_SLOT_OPENGL;
	};
}
