#pragma once
#include "points.h"
#include "Matrix3.h"

class Matrix4
{
private:
	float m[4][4];
public:

	Matrix4() {}
	~Matrix4() {}

	Matrix4(const Matrix4 &ma);

	explicit Matrix4(const float arr[3][3]) { memcpy(m, arr, 9 * sizeof(float)); }


	Matrix4(float f1, float f2, float f3, float f4, float f5,
		float f6, float f7, float f8, float f9, float f10,
		float f11, float f12, float f13, float f14, float f15, float f16) {
		m[0][0] = f1, m[1][0] = f5, m[2][0] = f9, m[3][0] = f13;
		m[0][1] = f2, m[1][1] = f6, m[2][1] = f10, m[3][1] = f14;
		m[0][2] = f3, m[1][2] = f7, m[2][2] = f11, m[3][2] = f15;
		m[0][3] = f4, m[1][3] = f8, m[2][3] = f12, m[3][3] = f16;
	}

	Matrix4& operator = (const Matrix4 &ma);


	float* operator [] (int idx) { return m[idx]; }

	const float* operator [] (int idx) const { return m[idx]; }



	friend Matrix4 operator + (const Matrix4 &a, const Matrix4 &b);

	friend Matrix4 operator - (const Matrix4 &a, const Matrix4 &b);

	friend Matrix4 operator * (const Matrix4 &a, const Matrix4 &b);

	friend Vec4 operator * (const Vec4 &a, const Matrix4 &b);

	friend Vec4 operator *(const Matrix4 & a, const Vec4 & b);

	//to do:
	void makeZeroMatrix();
};

