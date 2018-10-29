#pragma once

#include <math.h>
#include <string>

namespace SimpleGameEngine::Math
{
	class Vec2
	{
	public:
		float x, y;

	public:
		/// <summary>
		/// Initializes a new instance of a 2D vector.
		/// </summary>
		Vec2();

		/// <summary>
		/// Initiailizes a new instance of a 2D vector.
		/// </summary>
		/// <param name="x">The x-coordinate.</param>
		/// <param name="y">The y-coordinate.</param>
		Vec2(float x, float y);

		/// <summary>
		/// Initializes a new instance of a 2D vector.
		/// </summary>
		/// <param name="other">The 2D vector to copy.</param>
		Vec2(const Vec2 &other);

		/// <summary>
		/// Desctructor.
		/// </summary>
		~Vec2();



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
		Vec2& add(float value);

		/// <summary>
		/// Adds a vector to this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec2& add(const Vec2 &other);
		
		/// <summary>
		/// Subtracts a scalar from this vector.
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		Vec2& subtract(float value);

		/// <summary>
		/// Subtracts a vector from this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec2& subtract(const Vec2 &other);

		/// <summary>
		/// Multiples a scalar with this vector.
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		Vec2& multiply(float value);
		
		/// <summary>
		/// Multiplies a vector with this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec2& multiply(const Vec2 &other);

		/// <summary>
		/// Divides this vector by a scalar.
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		Vec2& divide(float value);

		/// <summary>
		/// Divides this vector by a vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec2& divide(const Vec2 &other);

		/// <summary>
		/// Copies the values of another vector into this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec2& copy(const Vec2 &other);

		/// <summary>
		/// Checks if this vector is equal to another vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool equals(const Vec2 &other);

		std::string toString() const;



		/// <summary>
		/// Copies the elements of a vector into this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec2& operator=(const Vec2 &other);

		/// <summary>
		/// Adds a vector to this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec2& operator+=(const Vec2 &other);

		/// <summary>
		/// Subtracts a vector from this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec2& operator-=(const Vec2 &other);
		
		/// <summary>
		/// Multiples this vector with a vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec2& operator*=(const Vec2 &other);
		
		/// <summary>
		/// Divides this vector by a vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec2& operator/=(const Vec2 &other);



		/// <summary>
		/// Calculates the sum of two vectors.
		/// </summary>
		friend Vec2 operator+(Vec2 left, const Vec2 &right);

		/// <summary>
		/// Calculates the difference between two vectors.
		/// </summary>
		friend Vec2 operator-(Vec2 left, const Vec2 &right);

		/// <summary>
		/// Calculates the product of two vectors.
		/// </summary>
		friend Vec2 operator*(Vec2 left, const Vec2 &right);

		/// <summary>
		/// Calculates the quotient of two vectors.
		/// </summary>
		friend Vec2 operator/(Vec2 left, const Vec2 &right);
	};
}
