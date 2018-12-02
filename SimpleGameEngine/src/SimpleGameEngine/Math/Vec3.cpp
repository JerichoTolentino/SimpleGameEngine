#include "sgepch.h"
#include "Vec3.h"

namespace SimpleGameEngine::Math
{
	Vec3::Vec3()
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
	}

	Vec3::Vec3(float iX, float iY, float iZ)
	{
		this->x = iX;
		this->y = iY;
		this->z = iZ;
	}

	Vec3::Vec3(const Vec3 &other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
	}

	Vec3::~Vec3()
	{
	}



	float Vec3::length() const
	{
		return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
	}

	void Vec3::normalize()
	{
		float length = this->length();
		this->x /= length;
		this->y /= length;
		this->z /= length;
	}

	void Vec3::reverse()
	{
		this->x = -(this->x);
		this->y = -(this->y);
		this->z = -(this->z);
	}

	Vec3& Vec3::add(float value)
	{
		this->x += value;
		this->y += value;
		this->z += value;
		return *this;
	}

	Vec3& Vec3::subtract(float value)
	{
		this->x -= value;
		this->y -= value;
		this->z -= value;
		return *this;
	}

	Vec3& Vec3::multiply(float value)
	{
		this->x *= value;
		this->y *= value;
		this->z *= value;
		return *this;
	}

	Vec3& Vec3::divide(float value)
	{
		this->x /= value;
		this->y /= value;
		this->z /= value;
		return *this;
	}

	Vec3& Vec3::add(const Vec3 &other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return *this;
	}

	Vec3& Vec3::subtract(const Vec3 &other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		return *this;
	}

	Vec3& Vec3::multiply(const Vec3 &other)
	{
		this->x *= other.x;
		this->y *= other.y;
		this->z *= other.z;
		return *this;
	}

	Vec3& Vec3::divide(const Vec3 &other)
	{
		this->x /= other.x;
		this->y /= other.y;
		this->z /= other.z;
		return *this;
	}

	Vec3& Vec3::copy(const Vec3 &other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		return *this;
	}

	bool Vec3::equals(const Vec3 &other)
	{
		return (this->x == other.x && this->y == other.y && this->z == other.z);
	}

	std::string Vec3::toString() const
	{
		return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")";
	}



	Vec3& Vec3::operator=(const Vec3 &other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		return *this;
	}

	Vec3& Vec3::operator+=(const Vec3 &other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return *this;
	}

	Vec3& Vec3::operator-=(const Vec3 &other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		return *this;
	}

	Vec3& Vec3::operator*=(const Vec3 &other)
	{
		this->x *= other.x;
		this->y *= other.y;
		this->z *= other.z;
		return *this;
	}

	Vec3& Vec3::operator/=(const Vec3 &other)
	{
		this->x /= other.x;
		this->y /= other.y;
		this->z /= other.z;
		return *this;
	}



	Vec3 operator+(Vec3 left, const Vec3 &right)
	{
		left += right;
		return left;
	}

	Vec3 operator-(Vec3 left, const Vec3 &right)
	{
		left -= right;
		return left;
	}

	Vec3 operator*(Vec3 left, const Vec3 &right)
	{
		left *= right;
		return left;
	}

	Vec3 operator/(Vec3 left, const Vec3 &right)
	{
		left /= right;
		return left;
	}
}
