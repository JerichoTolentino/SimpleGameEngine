#include "sgepch.h"
#include "Mat4.h"

#include "MathException.h"

// Column Major Matrix
//	0	4	8	12
//	1	5	9	13
//	2	6	10	14
//	3	7	11	15

namespace SimpleGameEngine::Math
{
	Mat4::Mat4()
	{
		this->elements = new GLfloat[16]{
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0,
			0, 0, 0, 0
		};
	}

	Mat4::Mat4(const Mat4 &other)
	{
		this->elements = new GLfloat[16];

		memcpy(this->elements, other.elements, sizeof(float) * 16);
	}

	Mat4::~Mat4()
	{
		delete this->elements;
	}



	void Mat4::setIdentity()
	{
		memset((void*)elements, 0, sizeof(float) * 16);
		elements[0] = 1;
		elements[5] = 1;
		elements[10] = 1;
		elements[15] = 1;
	}

	void Mat4::clear()
	{
		memset((void*)elements, 0, sizeof(float) * 16);
	}

	void Mat4::transpose()
	{
		float temp;

		//swap 1 and 4
		temp = elements[1];
		elements[1] = elements[4];
		elements[4] = temp;

		//swap 2 and 8
		temp = elements[2];
		elements[2] = elements[8];
		elements[8] = temp;

		//swap 3 and 12
		temp = elements[3];
		elements[3] = elements[12];
		elements[12] = temp;

		//swap 6 and 9
		temp = elements[6];
		elements[6] = elements[9];
		elements[9] = temp;

		//swap 7 and 13
		temp = elements[7];
		elements[7] = elements[13];
		elements[13] = temp;

		//swap 11 and 14
		temp = elements[11];
		elements[11] = elements[14];
		elements[14] = temp;
	}

	void Mat4::inverse()
	{
		float a11 = elements[0];
		float a21 = elements[1];
		float a31 = elements[2];
		float a41 = elements[3];
		float a12 = elements[4];
		float a22 = elements[5];
		float a32 = elements[6];
		float a42 = elements[7];
		float a13 = elements[8];
		float a23 = elements[9];
		float a33 = elements[10];
		float a43 = elements[11];
		float a14 = elements[12];
		float a24 = elements[13];
		float a34 = elements[14];
		float a44 = elements[15];

		float determinant =
			a11 * a22 * a33 * a44 +
			a11 * a23 * a34 * a42 +
			a11 * a24 * a32 * a43 +
			a12 * a21 * a34 * a43 +
			a12 * a23 * a31 * a44 +
			a12 * a24 * a33 * a41 +
			a13 * a21 * a32 * a44 +
			a13 * a22 * a34 * a41 +
			a13 * a24 * a31 * a42 +
			a14 * a21 * a33 * a42 +
			a14 * a22 * a31 * a43 +
			a14 * a23 * a32 * a41 -
			a11 * a22 * a34 * a43 -
			a11 * a23 * a32 * a44 -
			a11 * a24 * a33 * a42 -
			a12 * a21 * a33 * a44 -
			a12 * a23 * a34 * a41 -
			a12 * a24 * a31 * a43 -
			a13 * a21 * a34 * a42 -
			a13 * a22 * a31 * a44 -
			a13 * a24 * a32 * a41 -
			a14 * a21 * a32 * a43 -
			a14 * a22 * a33 * a41 -
			a14 * a23 * a31 * a42;

		//NOTE: if determinant is 0, inverse matrix doesn't exist! (Can't 'really' check because of floating pt rounding..)
		if (determinant == 0)
		{
			throw MathException("Determinant of inverse matrix is 0.");
		}

		float *temp = new float[16];
		temp[0] =
			a22 * a33 * a44 +
			a23 * a34 * a42 +
			a24 * a32 * a43 -
			a22 * a34 * a43 -
			a23 * a32 * a44 -
			a24 * a33 * a42;
		temp[4] =
			a12 * a34 * a43 +
			a13 * a32 * a44 +
			a14 * a33 * a42 -
			a12 * a33 * a44 -
			a13 * a34 * a42 -
			a14 * a32 * a43;
		temp[8] =
			a12 * a23 * a44 +
			a13 * a24 * a42 +
			a14 * a22 * a43 -
			a12 * a24 * a43 -
			a13 * a22 * a44 -
			a14 * a23 * a42;
		temp[12] =
			a12 * a24 * a33 +
			a13 * a22 * a34 +
			a14 * a23 * a32 -
			a12 * a23 * a34 -
			a13 * a24 * a32 -
			a14 * a22 * a33;

		/////////////////////////////////////////////////

		temp[1] =
			a21 * a34 * a43 +
			a23 * a31 * a44 +
			a24 * a33 * a41 -
			a21 * a33 * a44 -
			a23 * a34 * a41 -
			a24 * a31 * a43;

		temp[5] =
			a11 * a33 * a44 +
			a13 * a34 * a41 +
			a14 * a31 * a43 -
			a11 * a34 * a43 -
			a13 * a31 * a44 -
			a14 * a33 * a41;

		temp[9] =
			a11 * a24 * a43 +
			a13 * a21 * a44 +
			a14 * a23 * a41 -
			a11 * a23 * a44 -
			a13 * a24 * a41 -
			a14 * a21 * a43;

		temp[13] =
			a11 * a23 * a34 +
			a13 * a24 * a31 +
			a14 * a21 * a33 -
			a11 * a24 * a33 -
			a13 * a21 * a34 -
			a14 * a23 * a41;

		/////////////////////////////////////////////////

		temp[2] =
			a21 * a32 * a44 +
			a22 * a34 * a41 +
			a24 * a31 * a42 -
			a21 * a34 * a42 -
			a22 * a31 * a44 -
			a24 * a32 * a41;

		temp[6] =
			a11 * a34 * 42 +
			a12 * a31 * a44 +
			a14 * a32 * a41 -
			a11 * a32 * a44 -
			a12 * a34 * a41 -
			a14 * a31 * a42;

		temp[10] =
			a11 * a22 * a44 +
			a12 * a24 * a41 +
			a14 * a21 * a42 -
			a11 * a24 * a42 -
			a12 * a21 * a44 -
			a14 * a22 * a41;

		temp[14] =
			a11 * a24 * a32 +
			a12 * a21 * a34 +
			a14 * a22 * a31 -
			a11 * a22 * a34 -
			a12 * a24 * a31 -
			a14 * a21 * a32;

		/////////////////////////////////////////////////

		temp[3] =
			a21 * a33 * a42 +
			a22 * a31 * a43 +
			a23 * a32 * a41 -
			a21 * a32 * a43 -
			a22 * a33 * a41 -
			a23 * a31 * a42;

		temp[7] =
			a11 * a32 * a43 +
			a12 * a33 * a41 +
			a13 * a31 * a42 -
			a11 * a33 * a42 -
			a12 * a31 * a43 -
			a13 * a32 * a41;

		temp[11] =
			a11 * a23 * a42 +
			a12 * a21 * a43 +
			a13 * a22 * a41 -
			a11 * a22 * a43 -
			a12 * a23 * a41 -
			a13 * a21 * a42;

		temp[15] =
			a11 * a22 * a33 +
			a12 * a23 * a31 +
			a13 * a21 * a32 -
			a11 * a23 * a32 -
			a12 * a21 * a33 -
			a13 * a22 * a31;

		/////////////////////////////////////////////////

		for (int i = 0; i < 16; i++)
			temp[i] /= determinant;

		memcpy(this->elements, temp, sizeof(float) * 16);
		delete temp;
	}

	void Mat4::setElements(float e[16])
	{
		memcpy(this->elements, e, sizeof(float) * 16);
	}

	void Mat4::transform(const Vec3 & translate, const Vec3 & rotate, const Vec3 & scale)
	{
		Mat4 transformations;

		transformations.setIdentity();

		transformations *= generateTranslation(translate);

		transformations *= generateRotation(rotate.x, Vec3(1, 0, 0));
		transformations *= generateRotation(rotate.y, Vec3(0, 1, 0));
		transformations *= generateRotation(rotate.z, Vec3(0, 0, 1));

		transformations *= generateScaling(scale);

		*this *= transformations;
	}

	std::string Mat4::toString() const
	{
		std::string output;

		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				int index = row + 4 * col;
				output += std::to_string(elements[index]);
				output += "\t";
			}
			output += "\n";
		}

		return output;
	}



	Mat4& Mat4::operator=(const Mat4 &other)
	{
		memcpy(this->elements, other.elements, sizeof(float) * 16);
		return *this;
	}

	Mat4& Mat4::operator+=(const Mat4 &other)
	{
		for (int i = 0; i < 16; i++)
			this->elements[i] += other.elements[i];
		return *this;
	}

	Mat4& Mat4::operator-=(const Mat4 &other)
	{
		for (int i = 0; i < 16; i++)
			this->elements[i] -= other.elements[i];
		return *this;
	}

	Mat4& Mat4::operator*=(const Mat4 &other)
	{
		float a11 = elements[0];
		float a21 = elements[1];
		float a31 = elements[2];
		float a41 = elements[3];
		float a12 = elements[4];
		float a22 = elements[5];
		float a32 = elements[6];
		float a42 = elements[7];
		float a13 = elements[8];
		float a23 = elements[9];
		float a33 = elements[10];
		float a43 = elements[11];
		float a14 = elements[12];
		float a24 = elements[13];
		float a34 = elements[14];
		float a44 = elements[15];

		float b11 = other.elements[0];
		float b21 = other.elements[1];
		float b31 = other.elements[2];
		float b41 = other.elements[3];
		float b12 = other.elements[4];
		float b22 = other.elements[5];
		float b32 = other.elements[6];
		float b42 = other.elements[7];
		float b13 = other.elements[8];
		float b23 = other.elements[9];
		float b33 = other.elements[10];
		float b43 = other.elements[11];
		float b14 = other.elements[12];
		float b24 = other.elements[13];
		float b34 = other.elements[14];
		float b44 = other.elements[15];

		elements[0] = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41;
		elements[1] = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41;
		elements[2] = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41;
		elements[3] = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41;

		elements[4] = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42;
		elements[5] = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42;
		elements[6] = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42;
		elements[7] = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42;

		elements[8] = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43;
		elements[9] = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43;
		elements[10] = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43;
		elements[11] = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43;

		elements[12] = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44;
		elements[13] = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44;
		elements[14] = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44;
		elements[15] = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44;

		return *this;
	}

	Mat4 operator+(Mat4 left, const Mat4 &right)
	{
		Mat4 sum;

		for (int i = 0; i < 16; i++)
			sum.elements[i] = left.elements[i] + right.elements[i];

		return sum;
	}

	Mat4 operator-(Mat4 left, const Mat4 &right)
	{
		Mat4 difference;

		for (int i = 0; i < 16; i++)
			difference.elements[i] = left.elements[i] - right.elements[i];

		return difference;
	}

	Mat4 operator*(Mat4 left, const Mat4 &right)
	{
		Mat4 product;
		product = left;
		product *= right;
		return product;
	}

	Vec4 operator*(Mat4 left, const Vec4 & right)
	{
		Vec4 result;
		
		result.x = 
			left.elements[0]  * right.x +
			left.elements[4]  * right.y +
			left.elements[8]  * right.z +
			left.elements[12] * right.w;

		result.y =
			left.elements[1]  * right.x +
			left.elements[5]  * right.y +
			left.elements[9]  * right.z +
			left.elements[13] * right.w;

		result.z =
			left.elements[2]  * right.x +
			left.elements[6]  * right.y +
			left.elements[10] * right.z +
			left.elements[14] * right.w;

		result.w =
			left.elements[3]  * right.x +
			left.elements[7]  * right.y +
			left.elements[11] * right.z +
			left.elements[15] * right.w;

		return result;
	}



	Mat4 Mat4::generateProjectionMatrix(float aspectRatio, float fov, float nearClip, float farClip)
	{
		Mat4 projection;

		float s = (float) (1.0 / tan(fov * PI / 360));
		float fmn = farClip - nearClip;

		projection.elements[0] = s / aspectRatio;
		projection.elements[5] = s;
		projection.elements[10] = -(farClip + nearClip) / fmn;
		projection.elements[11] = -1;
		projection.elements[14] = -2 * farClip * nearClip / fmn;
		projection.elements[15] = 0;

		return projection;
	}

	Mat4 Mat4::generateViewMatrix(const Vec3 & cameraPos, const Vec3 & cameraRot)
	{
		Mat4 view;
		view.setIdentity();

		view *= generateRotation(cameraRot.x, Vec3(1, 0, 0));
		view *= generateRotation(cameraRot.y, Vec3(0, 1, 0));
		view *= generateRotation(cameraRot.z, Vec3(0, 0, 1));

		view *= generateTranslation(Vec3(-cameraPos.x, -cameraPos.y, -cameraPos.z));

		return view;

	}

	Mat4 Mat4::generateNormalMatrix(const Mat4 & modelMatrix)
	{
		Mat4 normalMatrix = modelMatrix;

		normalMatrix.elements[12] = 0;
		normalMatrix.elements[13] = 0;
		normalMatrix.elements[14] = 0;

		return normalMatrix;
	}


	Mat4 Mat4::generateRotation(float angle, const Vec3 & axis)
	{
		Mat4 rotate;
		float x = axis.x;
		float y = axis.y;
		float z = axis.z;
		float rAngle = MathUtils::toRadians(angle);
		float c = cos(rAngle);
		float s = sin(rAngle);
		float omc = 1 - cos(rAngle);
		rotate.setIdentity();

		rotate.elements[0] = (x * x) * omc + c;
		rotate.elements[1] = (x * y) * omc + z * s;
		rotate.elements[2] = (x * z) * omc - y * s;

		rotate.elements[4] = (x * y) * omc - z * s;
		rotate.elements[5] = (y * y) * omc + c;
		rotate.elements[6] = (y * z) * omc + x * s;

		rotate.elements[8] = (x * z) * omc + y * s;
		rotate.elements[9] = (y * z) * omc - x * s;
		rotate.elements[10] = (z * z) * omc + c;

		return rotate;
	}

	Mat4 Mat4::generateTranslation(const Vec3 & translate)
	{
		Mat4 translation;

		translation.setIdentity();

		translation.elements[12] = translate.x;
		translation.elements[13] = translate.y;
		translation.elements[14] = translate.z;

		return translation;
	}

	Mat4 Mat4::generateScaling(const Vec3 & scale)
	{
		Mat4 scaling;

		scaling.elements[0] = scale.x;
		scaling.elements[5] = scale.y;
		scaling.elements[10] = scale.z;
		scaling.elements[15] = 1;

		return scaling;
	}
}
