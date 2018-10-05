#include "Matrix4.h"
#include <iostream>



Matrix4& Matrix4::operator = (const Matrix4 &ma) {
	memcpy(m, ma.m, 16 * sizeof(float));
	return *this;
}


Matrix4::Matrix4(const Matrix4 &ma) {
	memcpy(m, ma.m, 16 * sizeof(float));
}


Matrix4 operator+(const Matrix4 & a, const Matrix4 & b) {
	Matrix4 answer;
	memset(answer.m, 0, 16 * sizeof(float));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			answer[i][j] = a[i][j] + b[i][j];
		}
	}
	return answer;
}


Matrix4 operator-(const Matrix4 & a, const Matrix4 & b) {
	Matrix4 answer;
	memset(answer.m, 0, 16 * sizeof(float));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			answer[i][j] = a[i][j] - b[i][j];
		}
	}
	return answer;
}


Matrix4 operator*(const Matrix4 & a, const Matrix4 & b) {
	Matrix4 answer;
	memset(answer.m, 0, 16 * sizeof(float));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				answer[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return answer;
}


Vec4 operator*(const Vec4 & a, const Matrix4 & b) {
	Vec4 answer;
	memset(answer.val, 0, 4 * sizeof(float));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			answer[i] += a[i] * b[j][i];
		}
	}
	return answer;
}


Vec4 operator*(const Matrix4 & a, const Vec4 & b) {
	Vec4 answer;
	memset(answer.val, 0, 4 * sizeof(float));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			answer[i] += a[i][j] * b[j];
		}
	}
	return answer;
}


void Matrix4::setIdentityMatrix() {
	memset(m, 0, sizeof(float) * 16);
	for (int i = 0; i < 4; i++) {
		m[i][i] = 1;
	}
}