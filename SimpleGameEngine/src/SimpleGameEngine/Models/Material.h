#pragma once
#include <GL/glew.h>
#include <string>
#include "LightingModel.h"

namespace SimpleGameEngine::Models
{
	class Material
	{
	private:
		GLuint m_textureId;
		LightingModel m_lightingModel;



	public:
		Material();
		Material(GLuint textureId, LightingModel lightingModel);
		Material(const Material &other);
		virtual ~Material();



		GLuint getTextureID() const;
		LightingModel getLightingModel() const;
		void setTextureID(GLuint id);
		void setLightingModel(LightingModel lightingModel);



		Material& operator=(const Material &other);
	};
}
