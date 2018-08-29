#pragma once
#include <string>
#include <fstream>

//Vec3 def
struct Vec3
{
	float x, y, z;

	Vec3();

	Vec3(float, float, float);

	Vec3(const Vec3&);

	Vec3& operator =(const Vec3&);

	friend Vec3 operator -(const Vec3&, const Vec3&);

	friend Vec3 operator +(const Vec3&, const Vec3&);

	friend Vec3 operator *(float num, const Vec3&);

	~Vec3();
};

//Vec2 def
struct Vec2
{
	float x, y;

	Vec2();

	Vec2(float, float);

	Vec2(int, int);

	Vec2(const Vec2&);

	Vec2& operator =(const Vec2&);


	friend Vec2 operator -(const Vec2&, const Vec2&);

	friend Vec2 operator +(const Vec2&, const Vec2&);

	friend Vec2 operator *(float num, const Vec2&);


	~Vec2();
};

//Polygon def
struct Polygon
{
	int vertex[3], normal[3], texture[3];

	Polygon();

	Polygon(std::ifstream &is);

	Polygon(const Polygon&);


	Polygon& operator =(const Polygon&);

	~Polygon();
};