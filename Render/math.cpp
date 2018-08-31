#include "stdafx.h"
#include "math.h"
#include <cmath>
//Function decl

float Math::_length(const Vec3 &v) {
	return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

float Math::_square(const Vec2 &v1, const Vec2 &v2, const Vec2 &v3) {
	Vec3 val = crossPrt(Vec3(v1[0], v2[0], v3[0]), Vec3(v1[1], v2[1], v3[1]));
	return abs(val[0] + val[1] + val[2]) / 2.;
}

Vec3 Math::normalize(const Vec3 &v)
{
	Vec3 answer = v;
	float length = _length(answer);

	answer[0] /= length;
	answer[1] /= length;
	answer[2] /= length;

	return answer;
}


bool Math::intersectionTrglPn(const Vec2 &v1, const Vec2 &v2, const Vec2 &v3, const Vec2 &pn) {
	if (abs(_square(v1, v2, v3) - (_square(v1, v2, pn) + _square(v1, v3, pn) + _square(v2, v3, pn))) < 0.01) {
		return true;
	}
	else {
		return false;
	}
}

float Math::scalarPrt3(const Vec3 &a, const Vec3 &b)
{
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

float Math::scalarPrt2(const Vec2 &a, const Vec2 &b)
{
	return a[0] * b[0] + a[1] * b[1];
}

Vec3 Math::crossPrt(const Vec3 &v1, const Vec3 &v2) {
	return Vec3{ v1[1] * v2[2] - v1[2] * v2[1], - v1[0] * v2[2] + v1[2] * v2[0], v1[0] * v2[1] - v1[1] * v2[0] };
}

Vec3 Math::rotate(const Vec3 &pn, float alpha, float beta, float zet) {
	Vec3 answer;
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