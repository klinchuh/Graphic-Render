#pragma once
#include "stdafx.h"
#include "points.h"


class Math {
public:

	//Length of vector
	static float _length(const Vec3 &v);

	//Square of triangle
	static float _square(const Vec2 &v1, const Vec2 &v2, const Vec2 &v3);

	//Normalize vector
	static Vec3 normalize(const Vec3 &v);

	//Point in triangle test
	static bool intersectionTrglPn(const Vec2 &v1, const Vec2 &v2, const Vec2 &v3, const Vec2 &pn);

	//Scalar product of 2 vectors in space
	static float scalarPrt3(const Vec3 &a, const Vec3 &b);
	//Scalar product of 2 vectors on plane
	static float scalarPrt2(const Vec2 &a, const Vec2 &b);


	//Cross product of 2 vectors
	static Vec3 crossPrt(const Vec3 &v1, const Vec3 &v2);


	//Rotate vector on SCENE_ROTATE angles
	static Vec3 rotate(const Vec3 &pn, float alpha, float beta, float zet);

};