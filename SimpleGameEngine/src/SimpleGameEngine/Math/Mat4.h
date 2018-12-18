#pragma once
#include <string>
#include <iostream>
#include <math.h>
#include <GL/glew.h>

#include "Vec3.h"
#include "Vec4.h"
#include "MathUtils.h"

namespace SimpleGameEngine::Math
{
	class Mat4
	{

	public:
		GLfloat *elements;

	public:
		/// <summary>
		/// Initializes a new instance of a 4x4 matrix.
		/// </summary>
		Mat4();

		/// <summary>
		/// Copy constructor.
		/// </summary>
		/// <param name="other"></param>
		Mat4(const Mat4 &other);

		/// <summary>
		/// Desctructor.
		/// </summary>
		~Mat4();



		/// <summary>
		/// Sets this matrix to an identity matrix.
		/// </summary>
		void setIdentity();

		/// <summary>
		/// Sets all elements in this matrix to 0.
		/// </summary>
		void clear();

		/// <summary>
		/// Flips this matrix along the main diagonal.
		/// </summary>
		void transpose();

		/// <summary>
		/// Sets this matrix to be the inverse of itself.
		/// </summary>
		/// <exception cref="MathException"></exception>
		void inverse();

		/// <summary>
		/// Copies the values in the specified column major matrix to this matrix.
		/// </summary>
		/// <param name="e">The matrix to copy from.</param>
		void setElements(float e[16]);

		/// <summary>
		/// Transforms this matrix by the given transformation vectors.
		/// </summary>
		/// <param name="translate">The vector to translate this matrix with.</param>
		/// <param name="rotate">The vector to rotate this matrix with.</param>
		/// <param name="scale">The vector to scale this matrix with.</param>
		void transform(const Vec3 & translate, const Vec3 & rotate, const Vec3 & scale);

		std::string toString() const;



		/// <summary>
		/// Copies the specified matrix's elements into this matrix.
		/// </summary>
		/// <param name="other">The matrix to copy elements from.</param>
		/// <returns></returns>
		Mat4& operator=(const Mat4 &other);

		/// <summary>
		/// Adds the specified matrix to this matrix.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Mat4& operator+=(const Mat4 &other);

		/// <summary>
		/// Subtracts the specified matrix from this matrix.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Mat4& operator-=(const Mat4 &other);

		/// <summary>
		/// Multiplies the specified matrix with this matrix to get the cross product.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Mat4& operator*=(const Mat4 &other);

		/// <summary>
		/// Calculates the sum of two matrices.
		/// </summary>
		friend Mat4 operator+(Mat4 left, const Mat4 &right);

		/// <summary>
		/// Calculates the difference between two matrices.
		/// </summary>
		friend Mat4 operator-(Mat4 left, const Mat4 &right);

		/// <summary>
		/// Calculates the cross product of two matrices.
		/// </summary>
		friend Mat4 operator*(Mat4 left, const Mat4 &right);

		/// <summary>
		/// Calculates the dot product of a <see cref="Mat4"/> with a <see cref="Vec4"/>.
		/// </summary>
		friend Vec4 operator*(Mat4 left, const Vec4 & right);



		/// <summary>
		/// Generates a project matrix.
		/// </summary>
		/// <param name="aspectRatio">The aspect ratio.</param>
		/// <param name="fov">The field of view in degrees.</param>
		/// <param name="near">The near clipping plane.</param>
		/// <param name="far">The far clipping plane.</param>
		/// <returns></returns>
		static Mat4 generateProjectionMatrix(float aspectRatio, float fov, float near, float far);

		/// <summary>
		/// Generates a view matrix.
		/// </summary>
		/// <param name="sourcePos">The position vector of the view source.</param>
		/// <param name="sourceRot">The rotation vector of the view source.</param>
		/// <returns></returns>
		static Mat4 generateViewMatrix(const Vec3 & sourcePos, const Vec3 & sourceRot);

		/// <summary>
		/// Generates a normal matrix.
		/// </summary>
		/// <param name="modelMatrix">The model matrix to generate a normal matrix for.</param>
		/// <returns></returns>
		static Mat4 generateNormalMatrix(const Mat4 & modelMatrix);



	private:
		/// <summary>
		/// Generates a rotation matrix.
		/// </summary>
		/// <param name="angle">The angle in degrees.</param>
		/// <param name="axis">The axis vector to rotate around.</param>
		/// <returns></returns>
		static Mat4 generateRotation(float angle, const Vec3 & axis);

		/// <summary>
		/// Generates a translation matrix.
		/// </summary>
		/// <param name="translate">The translation vector.</param>
		/// <returns></returns>
		static Mat4 generateTranslation(const Vec3 & translate);

		/// <summary>
		/// Generates a scale matrix.
		/// </summary>
		/// <param name="scale">The scaling vector.</param>
		/// <returns></returns>
		static Mat4 generateScaling(const Vec3 & scale);

	};
}
