#pragma once
#include <string>
#include <fstream>

//Vec4 def
class Vec4
{
public:
	float val[4];
	Vec4() {}

	Vec4(float, float, float, float);

	Vec4(const Vec4&);

	Vec4& operator =(const Vec4&);

	friend Vec4 operator -(const Vec4&, const Vec4&);

	friend Vec4 operator +(const Vec4&, const Vec4&);

	friend Vec4 operator *(float num, const Vec4&);

	float& operator [](int num) { return val[num]; }

	const float& operator [](int num) const { return val[num]; }

	~Vec4() {}
};

//Vec3 def
class Vec3
{
public:
	float val[3];
	Vec3() {}

	Vec3(float, float, float);

	Vec3(const Vec3&);

	Vec3& operator =(const Vec3&);

	friend Vec3 operator -(const Vec3&, const Vec3&);

	friend Vec3 operator +(const Vec3&, const Vec3&);

	friend Vec3 operator *(float num, const Vec3&);

	inline float& operator [](int num) { return val[num]; }

	inline const float& operator [](int num) const { return val[num]; }

	static Vec3 project4To3(const Vec4 &vc) {
		return Vec3(vc[0] / vc[3], vc[1] / vc[3], vc[2] / vc[3]);
	}

	~Vec3() {}
};

//Vec2 def
struct Vec2
{
private:
	float val[2];
public:

	Vec2() {}

	Vec2(float, float);

	Vec2(int, int);

	Vec2(const Vec2&);

	Vec2& operator =(const Vec2&);


	friend Vec2 operator -(const Vec2&, const Vec2&);

	friend Vec2 operator +(const Vec2&, const Vec2&);

	friend Vec2 operator *(float num, const Vec2&);


	inline float& operator [](int num) { return val[num]; }

	inline const float& operator [](int num) const { return val[num]; }

	~Vec2() {}
};

//Polygon def
struct Polygon3
{
	int vertex[3], normal[3], texture[3];

	Polygon3();

	Polygon3(std::ifstream &is);

	Polygon3(const Polygon3&);

	Polygon3& operator =(const Polygon3&);

	~Polygon3();
};