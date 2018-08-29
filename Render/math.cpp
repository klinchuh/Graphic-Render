#include "stdafx.h"
#include "math.h"
#include <cmath>
//Function decl

float _length(const Vec3 &v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float _square(const Vec2 &v1, const Vec2 &v2, const Vec2 &v3) {
	Vec3 val = crossPrt(Vec3{ v1.x, v2.x, v3.x }, Vec3{ v1.y, v2.y, v3.y });
	return abs(val.x + val.y + val.z) / 2.;
}

Vec3 normalize(const Vec3 &v)
{
	Vec3 answer = v;
	float length = _length(answer);

	answer.x /= length;
	answer.y /= length;
	answer.z /= length;

	return answer;
}


bool intersectionTrglPn(const Vec2 &v1, const Vec2 &v2, const Vec2 &v3, const Vec2 &pn) {
	if (abs(_square(v1, v2, v3) - (_square(v1, v2, pn) + _square(v1, v3, pn) + _square(v2, v3, pn))) < 0.01) {
		return true;
	}
	else {
		return false;
	}
}

float scalarPrt3(const Vec3 &a, const Vec3 &b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float scalarPrt2(const Vec2 &a, const Vec2 &b)
{
	return a.x * b.x + a.y * b.y;
}

Vec3 crossPrt(const Vec3 &v1, const Vec3 &v2) {
	return Vec3{ v1.y * v2.z - v1.z * v2.y, - v1.x * v2.z + v1.z * v2.x, v1.x * v2.y - v1.y * v2.x };
}

Vec3 rotate(const Vec3 &pn, float alpha, float beta, float zet) {
	Vec3 answer;
	answer.x = cos(alpha) * pn.x + sin(alpha) * pn.z;
	answer.y = pn.y;
	answer.z = -sin(alpha) * pn.x + cos(alpha) * pn.z;

	answer.x = answer.x;
	answer.y = answer.y * cos(beta) + answer.z * (-sin(beta));
	answer.z = answer.y * sin(beta) + answer.z * (cos(beta));

	answer.x = cos(zet) * answer.x + answer.y * sin(zet);
	answer.y = -sin(zet) *	answer.x + answer.y * cos(zet);
	answer.z = answer.z;

	return answer;
}