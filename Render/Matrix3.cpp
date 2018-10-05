#include "Matrix3.h"


Matrix3& Matrix3::operator = (const Matrix3 &ma) {
	memcpy(m, ma.m, 9 * sizeof(float));
	return *this;
}


Matrix3::Matrix3(const Matrix3 &ma) {
	memcpy(m, ma.m, 9 * sizeof(float));
}


Matrix3 operator + (const Matrix3 & a, const Matrix3 & b) {
	Matrix3 answer;
	memset(answer.m, 0, 9 * sizeof(float));
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
				answer[i][j] = a[i][j] + b[i][j];
		}
	}
	return answer;
}


Matrix3 operator - (const Matrix3 & a, const Matrix3 & b) {
	Matrix3 answer;
	memset(answer.m, 0, 9 * sizeof(float));
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			answer[i][j] = a[i][j] - b[i][j];
		}
	}
	return answer;
}


Matrix3 operator * (const Matrix3 & a, const Matrix3 & b) {
	Matrix3 answer;
	memset(answer.m, 0, 9 * sizeof(float));
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				answer[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	return answer;
}


Vec3 operator * (const Vec3 & a, const Matrix3 & b) {
	Vec3 answer;
	memset(answer.val, 0, 3 * sizeof(float));
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			answer[i] += a[i] * b[j][i];
		}
	}
	return answer;
}


void Matrix3::setIdentityMatrix() {
	memset(m, 0, sizeof(float) * 9);
	for (int i = 0; i < 3; i++) {
		m[i][i] = 1;
	}
}