#include "Vec4.h"

namespace SimpleGameEngine::Math
{
	Vec4::Vec4()
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->w = 0.0f;
	}

	Vec4::Vec4(float iX, float iY, float iZ, float iW)
	{
		this->x = iX;
		this->y = iY;
		this->z = iZ;
		this->w = iW;
	}

	Vec4::Vec4(const Vec4 &other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		this->w = other.w;
	}

	Vec4::~Vec4()
	{
	}



	float Vec4::length() const
	{
		return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w));
	}

	void Vec4::normalize()
	{
		float length = this->length();
		this->x /= length;
		this->y /= length;
		this->z /= length;
		this->w /= length;
	}

	void Vec4::reverse()
	{
		this->x = -(this->x);
		this->y = -(this->y);
		this->z = -(this->z);
		this->w = -(this->w);
	}

	Vec4& Vec4::add(float value)
	{
		this->x += value;
		this->y += value;
		this->z += value;
		this->w += value;
		return *this;
	}

	Vec4& Vec4::add(const Vec4 &other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		this->w += other.w;
		return *this;
	}

	Vec4& Vec4::subtract(float value)
	{
		this->x -= value;
		this->y -= value;
		this->z -= value;
		this->w -= value;
		return *this;
	}

	Vec4& Vec4::subtract(const Vec4 &other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		this->w -= other.w;
		return *this;
	}

	Vec4& Vec4::multiply(float value)
	{
		this->x *= value;
		this->y *= value;
		this->z *= value;
		this->w *= value;
		return *this;
	}

	Vec4& Vec4::multiply(const Vec4 &other)
	{
		this->x *= other.x;
		this->y *= other.y;
		this->z *= other.z;
		this->w *= other.w;
		return *this;
	}

	Vec4& Vec4::divide(float value)
	{
		this->x /= value;
		this->y /= value;
		this->z /= value;
		this->w /= value;
		return *this;
	}

	Vec4& Vec4::divide(const Vec4 &other)
	{
		this->x /= other.x;
		this->y /= other.y;
		this->z /= other.z;
		this->w /= other.w;
		return *this;
	}

	Vec4& Vec4::copy(const Vec4 &other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		this->w = other.w;
		return *this;
	}

	bool Vec4::equals(const Vec4 &other)
	{
		return (this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w);
	}
	
	std::string Vec4::toString() const
	{
		return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + "," + std::to_string(w) + ")";
	}



	Vec4& Vec4::operator=(const Vec4 &other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		this->w = other.w;
		return *this;
	}

	Vec4& Vec4::operator+=(const Vec4 &other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		this->w += other.w;
		return *this;
	}

	Vec4& Vec4::operator-=(const Vec4 &other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		this->w -= other.w;
		return *this;
	}

	Vec4& Vec4::operator*=(const Vec4 &other)
	{
		this->x *= other.x;
		this->y *= other.y;
		this->z *= other.z;
		this->w *= other.w;
		return *this;
	}

	Vec4& Vec4::operator/=(const Vec4 &other)
	{
		this->x /= other.x;
		this->y /= other.y;
		this->z /= other.z;
		this->w /= other.w;
		return *this;
	}



	Vec4 operator+(Vec4 left, const Vec4 &right)
	{
		left += right;
		return left;
	}

	Vec4 operator-(Vec4 left, const Vec4 &right)
	{
		left -= right;
		return left;
	}

	Vec4 operator*(Vec4 left, const Vec4 &right)
	{
		left *= right;
		return left;
	}

	Vec4 operator/(Vec4 left, const Vec4 &right)
	{
		left /= right;
		return left;
	}
}
