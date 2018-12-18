#pragma once
#include <math.h>
#include <string>

namespace SimpleGameEngine::Math
{
	class Vec3
	{
	public:
		float x, y, z;
	public:
		/// <summary>
		/// Initializes a new instance of a 3D vector.
		/// </summary>
		Vec3();

		/// <summary>
		/// Initiailizes a new instance of a 3D vector.
		/// </summary>
		/// <param name="x">The x-coordinate.</param>
		/// <param name="y">The y-coordinate.</param>
		Vec3(float iX, float iY, float iZ);

		/// <summary>
		/// Initializes a new instance of a 3D vector.
		/// </summary>
		/// <param name="other">The 3D vector to copy.</param>
		Vec3(const Vec3 &other);

		/// <summary>
		/// Desctructor.
		/// </summary>
		~Vec3();



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
		Vec3& add(float value);
		
		/// <summary>
		/// Adds a vector to this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec3& add(const Vec3 &other);
		
		/// <summary>
		/// Subtracts a scalar from this vector.
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		Vec3& subtract(float value);
		
		/// <summary>
		/// Subtracts a vector from this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec3& subtract(const Vec3 &other);
		
		/// <summary>
		/// Multiples a scalar with this vector.
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		Vec3& multiply(float value);
		
		/// <summary>
		/// Multiplies a vector with this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec3& multiply(const Vec3 &other);
		
		/// <summary>
		/// Divides this vector by a scalar.
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		Vec3& divide(float value);
		
		/// <summary>
		/// Divides this vector by a vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec3& divide(const Vec3 &other);
		
		/// <summary>
		/// Copies the values of another vector into this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec3& copy(const Vec3 &other);
		
		/// <summary>
		/// Checks if this vector is equal to another vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		bool equals(const Vec3 &other);
		
		std::string toString() const;



		/// <summary>
		/// Copies the elements of a vector into this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec3& operator=(const Vec3 &other);

		/// <summary>
		/// Adds a vector to this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec3& operator+=(const Vec3 &other);

		/// <summary>
		/// Subtracts a vector from this vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec3& operator-=(const Vec3 &other);

		/// <summary>
		/// Multiples this vector with a vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec3& operator*=(const Vec3 &other);

		/// <summary>
		/// Divides this vector by a vector.
		/// </summary>
		/// <param name="other"></param>
		/// <returns></returns>
		Vec3& operator/=(const Vec3 &other);



		/// <summary>
		/// Calculates the sum of two vectors.
		/// </summary>
		friend Vec3 operator+(Vec3 left, const Vec3 &right);

		/// <summary>
		/// Calculates the difference between two vectors.
		/// </summary>
		friend Vec3 operator-(Vec3 left, const Vec3 &right);

		/// <summary>
		/// Calculates the product of two vectors.
		/// </summary>
		friend Vec3 operator*(Vec3 left, const Vec3 &right);

		/// <summary>
		/// Calculates the quotient of two vectors.
		/// </summary>
		friend Vec3 operator/(Vec3 left, const Vec3 &right);

		/// <summary>
		/// Calculates the scalar product of a vector with a float.
		/// </summary>
		friend Vec3 operator*(Vec3 left, float right);



		/// <summary>
		/// Calculates the dot product of two <see cref="Vec3"/> instances.
		/// </summary>
		static float dot(const Vec3 & left, const Vec3 & right);

		/// <summary>
		/// Calculates the cross product of two <see cref="Vec3"/> instances.
		/// </summary>
		static Vec3 cross(const Vec3 & left, const Vec3 & right);
	};
}
