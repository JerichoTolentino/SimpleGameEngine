#include "EntityShaderConstants.h"

namespace SimpleGameEngine::Shaders
{
	const std::string EntityShaderConstants::VERT_MODEL_MATRIX = "u_model_matrix";
	const std::string EntityShaderConstants::VERT_PROJECTION_MATRIX = "u_proj_matrix";
	const std::string EntityShaderConstants::VERT_VIEW_MATRIX = "u_view_matrix";
	const std::string EntityShaderConstants::VERT_NORMAL_MATRIX = "u_normal_matrix";
	const std::string EntityShaderConstants::VERT_LIGHT_POSITION = "u_light_pos";
	const std::string EntityShaderConstants::VERT_EYE_POSITION = "u_eye_pos";

	const std::string FRAG_AMBIENT = "u_ambient";
	const std::string FRAG_EMISSIVE = "u_emissive";
	const std::string FRAG_DIFFUSE = "u_diffuse";
	const std::string FRAG_SPECULAR = "u_specular";
	const std::string FRAG_SPECULAR_HIGHLIGHT = "u_specular_highlight";
	const std::string FRAG_REFLECTIVITY = "u_reflectivity";
	const std::string FRAG_REFRACTIVE_INDEX = "u_refractive_index";
	const std::string FRAG_OPACITY = "u_opacity";
}