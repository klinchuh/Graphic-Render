#pragma once
#include "points.h" 

class Matrix3
{
private:
	float m[3][3];
public:

	Matrix3() {}

	~Matrix3() {}

	Matrix3(const Matrix3 &ma);

	explicit Matrix3(const float arr[3][3]) { memcpy(m, arr, 9 * sizeof(float)); }


	Matrix3(float f1, float f2, float f3, float f4,
		float f5, float f6, float f7, float f8, float f9) { 
		m[0][0] = f1;
		m[0][1] = f2;
		m[0][2] = f3;
		m[1][0] = f4;
		m[1][1] = f5;
		m[1][2] = f6;
		m[2][0] = f7;
		m[2][1] = f8;
		m[2][2] = f9;
	}
	

	Matrix3& operator = (const Matrix3 &ma);

	float* operator [] (int idx) { return m[idx];  }

	const float* operator [] (int idx) const { return m[idx]; }

	friend Matrix3 operator + (const Matrix3 &a, const Matrix3 &b);

	friend Matrix3 operator - (const Matrix3 &a, const Matrix3 &b);

	friend Matrix3 operator * (const Matrix3 &a, const Matrix3 &b);

	friend Vec3 operator * (const Vec3 &a, const Matrix3 &b);

	/*set as identify Matrix:
	[1, 0, 0]
	[0, 1, 0]
	[0, 0, 1]*/
	void setIdentityMatrix();

};

