#include "stdafx.h"
#include "points.h"

//Vec4 decl
Vec4::Vec4(float a, float b, float c, float d) { val[0] = a, val[1] = b, val[2] = c; val[3] = d; }

Vec4::Vec4(const Vec4 &pn) {
	val[0] = pn[0];
	val[1] = pn[1];
	val[2] = pn[2];
	val[3] = pn[3];
}

Vec4& Vec4::operator =(const Vec4 &pn) {
	val[0] = pn[0];
	val[1] = pn[1];
	val[2] = pn[2];
	val[3] = pn[3];
	return *this;
}

Vec4 operator -(const Vec4 &a, const Vec4 &b)
{
	return Vec4(a[0] - b[0], a[1] - b[1], a[2] - b[2], a[3] - b[3]);
}

Vec4 operator +(const Vec4 &a, const Vec4 &b)
{
	return Vec4(a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]);
}

Vec4 operator *(float num, const Vec4& v) {
	return Vec4(v[0] * num, v[1] * num, v[2] * num, v[3] * num);
}

//Vec3 decl
Vec3::Vec3(float a, float b, float c) { val[0] = a, val[1] = b, val[2] = c; }

Vec3::Vec3(const Vec3 &pn) {
	val[0] = pn[0];
	val[1] = pn[1];
	val[2] = pn[2];
}

Vec3& Vec3::operator =(const Vec3 &pn) {
	val[0] = pn[0];
	val[1] = pn[1];
	val[2] = pn[2];
	return *this;
}

Vec3 operator -(const Vec3 &a, const Vec3 &b)
{
	return Vec3(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
}

Vec3 operator +(const Vec3 &a, const Vec3 &b)
{
	return Vec3(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
}

Vec3 operator *(float num, const Vec3& v) {
	return Vec3(v[0] * num, v[1] * num, v[2] * num);
}

//Vec2 decl

Vec2::Vec2(float a, float b) { val[0] = a, val[1] = b; }

Vec2::Vec2(int a, int b)  { val[0] = a, val[1] = b; }

Vec2::Vec2(const Vec2 &pn) { val[0] = pn.val[0], val[1] = pn.val[1]; }

Vec2& Vec2::operator =(const Vec2 &pn) {
	val[0] = pn[0];
	val[1] = pn[1];
	return *this;
}


Vec2 operator -(const Vec2 &a, const Vec2 &b)
{
	return Vec2(a[0] - b[0], a[1] - b[1]);
}

Vec2 operator +(const Vec2 &a, const Vec2 &b)
{
	return Vec2(a[0] + b[0], a[1] + b[1]);
}

Vec2 operator *(float num, const Vec2& v) {
	return Vec2(v[0] * num, v[1] * num);
}


//Polygon decl

Polygon3::Polygon3() {}

Polygon3::Polygon3(std::ifstream &is) {
	int v1, v2, v3, vn1, vn2, vn3, vt1, vt2, vt3;
	char trash;
	is >> v1 >> trash >> vt1 >> trash >> vn1 >> v2 >> trash >> vt2 >> trash >> vn2 >> v3 >> trash >> vt3 >> trash >> vn3;
	//is >> v1 >> trash >> vt1 >> v2 >> trash >> vt2 >> v3 >> trash >> vt3;
	vertex[0] = v1 - 1;
	vertex[1] = v2 - 1;
	vertex[2] = v3 - 1;
	normal[0] = vn1 - 1;
	normal[1] = vn2 - 1;
	normal[2] = vn3 - 1;
	texture[0] = vt1 - 1;
	texture[1] = vt2 - 1;
	texture[2] = vt3 - 1;
}

Polygon3::Polygon3(const Polygon3 &pl) {
	memcpy(vertex, pl.vertex, 12);
	memcpy(normal, pl.normal, 12);
	memcpy(texture, pl.texture, 12);
}

Polygon3& Polygon3::operator =(const Polygon3 &pl) {
	memcpy(vertex, pl.vertex, 12);
	memcpy(normal, pl.normal, 12);
	memcpy(texture, pl.texture, 12);
	return *this;
}  

Polygon3::~Polygon3() {}
