#include "TerrainShaderConstants.h"

namespace SimpleGameEngine::Shaders
{
	const std::string TerrainShaderConstants::VERT_MODEL_MATRIX = "u_model_matrix";
	const std::string TerrainShaderConstants::VERT_PROJECTION_MATRIX = "u_proj_matrix";
	const std::string TerrainShaderConstants::VERT_VIEW_MATRIX = "u_view_matrix";
	const std::string TerrainShaderConstants::VERT_LIGHT_POSITION = "u_light_pos";

	const std::string TerrainShaderConstants::FRAG_AMBIENT = "u_ambient";
	const std::string TerrainShaderConstants::FRAG_DIFFUSE = "u_diffuse";
	const std::string TerrainShaderConstants::FRAG_OPACITY = "u_opacity";
	const std::string TerrainShaderConstants::FRAG_TILE_FACTOR = "u_tile_factor";
	const std::string TerrainShaderConstants::FRAG_BLEND_SAMPLER = "u_blend_sampler";
	const std::string TerrainShaderConstants::FRAG_RED_SAMPLER = "u_red_sampler";
	const std::string TerrainShaderConstants::FRAG_GREEN_SAMPLER = "u_green_sampler";
	const std::string TerrainShaderConstants::FRAG_BLUE_SAMPLER = "u_blue_sampler";
	const std::string TerrainShaderConstants::FRAG_BACKGROUND_SAMPLER = "u_back_sampler";

	const int TerrainShaderConstants::BLEND_MAP_TEXTURE_SLOT = 0;
	const int TerrainShaderConstants::RED_TEXTURE_SLOT = 1;
	const int TerrainShaderConstants::GREEN_TEXTURE_SLOT = 2;
	const int TerrainShaderConstants::BLUE_TEXTURE_SLOT = 3;
	const int TerrainShaderConstants::BACKGROUND_TEXTURE_SLOT = 4;

	const GLenum TerrainShaderConstants::BLEND_MAP_TEXTURE_SLOT_OPENGL = GL_TEXTURE0;
	const GLenum TerrainShaderConstants::RED_TEXTURE_SLOT_OPENGL = GL_TEXTURE1;
	const GLenum TerrainShaderConstants::GREEN_TEXTURE_SLOT_OPENGL = GL_TEXTURE2;
	const GLenum TerrainShaderConstants::BLUE_TEXTURE_SLOT_OPENGL = GL_TEXTURE3;
	const GLenum TerrainShaderConstants::BACKGROUND_TEXTURE_SLOT_OPENGL = GL_TEXTURE4;
}
