#pragma once
#include <GL/glew.h>
#include <string>

namespace SimpleGameEngine::Models
{
	class Material
	{
	private:
		GLuint textureID;
		float reflectivity, opacity, ambient, emissive, diffuse, specular, specularHighlight, refractiveIndex;
		std::string name;
	public:
		Material();
		Material(const Material &other);
		Material(std::string file, std::string n, GLuint texture, float a, float e, float d, float s, float sh, float ri, float r, float o);
		~Material();

		Material& operator=(const Material &other);

		GLuint getTextureID() const;
		float getReflectivity() const;
		float getOpacity() const;
		float getAmbient() const;
		float getEmissive() const;
		float getDiffuse() const;
		float getSpecular() const;
		float getSpecularHighlight() const;
		float getRefractiveIndex() const;

		void setTextureID(GLuint id);
		void setReflectivity(float r);
		void setOpacity(float o);
		void setAmbient(float a);
		void setEmissive(float e);
		void setDiffuse(float d);
		void setSpecular(float s);
		void setSpecularHighlight(float sh);
		void setRefractiveIndex(float ri);

		std::string toString() const;
	};
}
