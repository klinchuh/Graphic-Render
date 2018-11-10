#include "math.h"
#include <cmath>

float Math::_length(const glm::vec3 &v) {
	return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

float Math::_square(const glm::vec2 &v1, const glm::vec2 &v2, const glm::vec2 &v3) {
	glm::vec3 val = crossPrt(glm::vec3(v1[0], v2[0], v3[0]), glm::vec3(v1[1], v2[1], v3[1]));
	return fabs(val[0] + val[1] + val[2]) / 2.0f;
}

glm::vec3 Math::normalize(const glm::vec3 &v) {
	glm::vec3 answer = v;
	float length = _length(answer);

	answer[0] /= length;
	answer[1] /= length;
	answer[2] /= length;

	return answer;
}

bool Math::intersectionTrglPn(const glm::vec2 &v1, const glm::vec2 &v2, const glm::vec2 &v3, const glm::vec2 &pn) {
	if (abs(_square(v1, v2, v3) - (_square(v1, v2, pn) + _square(v1, v3, pn) + _square(v2, v3, pn))) < 0.01) {
		return true;
	}
	else {
		return false;
	}
}

float Math::scalarPrt3(const glm::vec3 &a, const glm::vec3 &b) {
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

float Math::scalarPrt2(const glm::vec2 &a, const glm::vec2 &b) {
	return a[0] * b[0] + a[1] * b[1];
}

glm::vec3 Math::crossPrt(const glm::vec3 &v1, const glm::vec3 &v2) {
	return glm::vec3{ v1[1] * v2[2] - v1[2] * v2[1], -v1[0] * v2[2] + v1[2] * v2[0], v1[0] * v2[1] - v1[1] * v2[0] };
}

glm::vec3 Math::rotate(const glm::vec3 &pn, float alpha, float beta, float zet) {
	glm::vec3 answer;
	answer[0] = cos(alpha) * pn[0] + sin(alpha) * pn[2];
	answer[1] = pn[1];
	answer[2] = -sin(alpha) * pn[0] + cos(alpha) * pn[2];

	answer[0] = answer[0];
	answer[1] = answer[1] * cos(beta) + answer[2] * (-sin(beta));
	answer[2] = answer[1] * sin(beta) + answer[2] * (cos(beta));

	answer[0] = cos(zet) * answer[0] + answer[1] * sin(zet);
	answer[1] = -sin(zet) *	answer[0] + answer[1] * cos(zet);
	answer[2] = answer[2];

	return answer;
}