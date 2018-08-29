#include "stdafx.h"
#include "points.h"

//Vec3 decl

Vec3::Vec3() {}

Vec3::Vec3(float a, float b, float c) : x(a), y(b), z(c) {}

Vec3::Vec3(const Vec3 &pn) {
	x = pn.x;
	y = pn.y;
	z = pn.z;
}

Vec3& Vec3::operator =(const Vec3 &pn) {
	x = pn.x;
	y = pn.y;
	z = pn.z;
	return *this;
}

Vec3 operator -(const Vec3 &a, const Vec3 &b)
{
	return Vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

Vec3 operator +(const Vec3 &a, const Vec3 &b)
{
	return Vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vec3 operator *(float num, const Vec3& v) {
	return Vec3(v.x * num, v.y * num, v.z * num);
}

Vec3::~Vec3() {}

//Vec2 decl

Vec2::Vec2() {}

Vec2::Vec2(float a, float b) : x(a), y(b) {}

Vec2::Vec2(int a, int b) : x(a), y(b) {}

Vec2::Vec2(const Vec2 &pn) {
	x = pn.x;
	y = pn.y;
}

Vec2& Vec2::operator =(const Vec2 &pn) {
	x = pn.x;
	y = pn.y;
	return *this;
}


Vec2 operator -(const Vec2 &a, const Vec2 &b)
{
	return Vec2(a.x - b.x, a.y - b.y);
}

Vec2 operator +(const Vec2 &a, const Vec2 &b)
{
	return Vec2(a.x + b.x, a.y + b.y);
}

Vec2 operator *(float num, const Vec2& v) {
	return Vec2(v.x * num, v.y * num);
}


Vec2::~Vec2() {}

//Polygon decl

Polygon::Polygon() {}

Polygon::Polygon(std::ifstream &is) {
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

Polygon::Polygon(const Polygon &pl) {
	memcpy(vertex, pl.vertex, 12);
	memcpy(normal, pl.normal, 12);
	memcpy(texture, pl.texture, 12);
}

Polygon& Polygon::operator =(const Polygon &pl) {
	memcpy(vertex, pl.vertex, 12);
	memcpy(normal, pl.normal, 12);
	memcpy(texture, pl.texture, 12);
	return *this;
}  

Polygon::~Polygon() {}
