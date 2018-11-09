#pragma once
#include "tgaimage.h"
#include "scene.h"
#include "math.h"
#include "Matrix4.h"


//{x, y, -z} - vector of light
const Vec3 LIGHT_VECTOR = {0., 0., 1.};


//main class with most improtant functions
class Render
{
public:
	const int sizeX = 700, sizeY = 700;

	bool RENDER_WITHOUT_TEXTURES;

	Render();
	~Render();

private:
	const float ZBUFFERDEEP = 1000;

	int *zBuffer;

	int *colorBuffer;

	Matrix4 perspectivViewMatrix, camViewMatrix, viewPort;

	/*1 - reset zBuffer
	2 - reset colorBuffer*/
	void resetParam();

	/*Drawing a line*/
	void drawLine(int x0, int y0, int x1, int y1, TGAImage &im, const TGAColor &color);

	/*Descript texture's point color*/
	TGAColor getTextureColor(const TGAImage &intx, const Vec2 &vt0, const Vec2 &vt1, const Vec2 &vt2, bool second, float alpha, float beta, float zet);

	/*The easyest method of drawing empty triangle*/
	void drawEmpTriangle(std::vector <Vec3> lst, TGAImage &im);

	/*Drawing a triangle with texture*/
	void drawTriangleWT(Vec3 v0, Vec3 v1, Vec3 v2,
		Vec2 vt0, Vec2 vt1, Vec2 vt2,
		Vec3 vn0, Vec3 vn1, Vec3 vn2,
		const TGAImage &texture);

	/*Get light Intensity of faces*/
	float getPolLightIntensity(const Vec3 &a, const Vec3 &b, const Vec3 &c);

	/*get shade inesity by Gouraund algorithm*/
	float getGouraudShadeIntesity(const Vec3 &vn0, const Vec3 &vn1, const Vec3 &vn2,
		bool second, float alpha, float beta, float zet);

	/*Rotate scene to currect(OZ to camera) position 
	and transform to display coord*/
	void transformToDisplayCoord(std::vector <Vec3> &list);

public:
	/*Preset Matrix for camera rotate
	val - value of perpectiv veiw*/
	void setProjection(float val);

	/*return const pointer to color buffer*/
	const int * getColorBuffer();

	/*eye - the camera point
	center - the point at which the camera is looking
	up - up of camera*/
	void lookAt(const Vec3 &eye, const Vec3 &center, const Vec3 &up);

	/*Scale Camera from [-1;1]x[-1;1]x[0;1] to [x;x+w]x[y;y+h]x[0;1]*/
	void setViewPort(int x, int y, int w, int h);

	/*Save scene in tga format file*/
	bool compileScene(Scene * sc);
	
};


