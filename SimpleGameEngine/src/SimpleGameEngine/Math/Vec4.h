#pragma once
#include <math.h>
#include <string>

namespace SimpleGameEngine::Math
{
	class Vec4
	{
	public:
		float x, y, z, w;
	public:
		/// <summary>
		/// Initializes a new instance of a 4D vector.
		/// </summary>
		Vec4();

		/// <summary>
		/// Initiailizes a new instance of a 4D vector.
		/// </summary>
		/// <param name="x">The x-coordinate.</param>
		/// <param name="y">The y-coordinate.</param>
		Vec4(float iX, float iY, float iZ, float iW);

		/// <summary>
		/// Initializes a new instance of a 4D vector.
		/// </summary>
		/// <param name="other">The 4D vector to copy.</param>
		Vec4(const Vec4 &other);

		/// <summary>
		/// Desctructor.
		/// </summary>
		~Vec4();



		/// <summary>
		/// Calculates the length of this vector.
		/// </summary>
		/// <returns></returns>
		float length() const;

		/// <summary>
		/// Normalizes this vector.
		/// </summary>
		void normalize();

		/// <summary>
		/// Reverses the direction of this vector.
		/// </summary>
		void reverse();

		/// <summary>
		/// Adds a scalar to this vector.
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		Vec4& add(float value);

		/// <summary>
		/// Adds a vector to this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec4& add(const Vec4 &other);

		/// <summary>
		/// Subtracts a scalar from this vector.
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		Vec4& subtract(float value);

		/// <summary>
		/// Subtracts a vector from this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec4& subtract(const Vec4 &other);

		/// <summary>
		/// Multiples a scalar with this vector.
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		Vec4& multiply(float value);

		/// <summary>
		/// Multiplies a vector with this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec4& multiply(const Vec4 &other);

		/// <summary>
		/// Divides this vector by a scalar.
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		Vec4& divide(float value);

		/// <summary>
		/// Divides this vector by a vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec4& divide(const Vec4 &other);

		/// <summary>
		/// Copies the values of another vector into this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec4& copy(const Vec4 &other);

		/// <summary>
		/// Checks if this vector is equal to another vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool equals(const Vec4 &other);

		std::string toString() const;



		/// <summary>
		/// Copies the elements of a vector into this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec4& operator=(const Vec4 &other);

		/// <summary>
		/// Adds a vector to this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec4& operator+=(const Vec4 &other);

		/// <summary>
		/// Subtracts a vector from this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec4& operator-=(const Vec4 &other);

		/// <summary>
		/// Multiples this vector with a vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec4& operator*=(const Vec4 &other);

		/// <summary>
		/// Divides this vector by a vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec4& operator/=(const Vec4 &other);



		/// <summary>
		/// Calculates the sum of two vectors.
		/// </summary>
		friend Vec4 operator+(Vec4 left, const Vec4 &right);

		/// <summary>
		/// Calculates the difference between two vectors.
		/// </summary>
		friend Vec4 operator-(Vec4 left, const Vec4 &right);

		/// <summary>
		/// Calculates the product of two vectors.
		/// </summary>
		friend Vec4 operator*(Vec4 left, const Vec4 &right);

		/// <summary>
		/// Calculates the quotient of two vectors.
		/// </summary>
		friend Vec4 operator/(Vec4 left, const Vec4 &right);
	};
}
