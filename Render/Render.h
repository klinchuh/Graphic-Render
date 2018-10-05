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
	static const int sizeX = 700, sizeY = 700;

	static int colorBuffer[sizeX * sizeY];

	static bool RENDER_WITHOUT_TEXTURES;

private:

	static int zBuffer[sizeX * sizeY];

	static Matrix4 perspectivViewMatrix, camViewMatrix, viewPort;

	static const float ZBUFFERDEEP;

	Render();
	~Render();

	/*1 - reset zBuffer
	2 - reset colorBuffer*/
	static void resetParam();

	/*Drawing a line*/
	static void drawLine(int x0, int y0, int x1, int y1, TGAImage &im, const TGAColor &color);

	/*Descript texture's point color*/
	static TGAColor getTextureColor(const TGAImage &intx, const Vec2 &vt0, const Vec2 &vt1, const Vec2 &vt2, bool second, float alpha, float beta, float zet);

	/*The easyest method of drawing empty triangle*/
	static void drawEmpTriangle(std::vector <Vec3> lst, TGAImage &im);

	/*Drawing a triangle with texture*/
	static void drawTriangleWT(Vec3 v0, Vec3 v1, Vec3 v2,
		Vec2 vt0, Vec2 vt1, Vec2 vt2,
		Vec3 vn0, Vec3 vn1, Vec3 vn2,
		const TGAImage &texture);

	/*Get light Intensity of faces*/
	static float getPolLightIntensity(const Vec3 &a, const Vec3 &b, const Vec3 &c);

	/*get shade inesity by Gouraund algorithm*/
	static float getGouraudShadeIntesity(const Vec3 &vn0, const Vec3 &vn1, const Vec3 &vn2,
		bool second, float alpha, float beta, float zet);

	/*Rotate scene to currect(OZ to camera) position 
	and transform to display coord*/
	static void transformToDisplayCoord(std::vector <Vec3> &list);

public:
	/*Preset Matrix for camera rotate
	val - value of perpectiv veiw*/
	static void setProjection(float val);

	/*eye - the camera point
	center - the point at which the camera is looking
	up - up of camera*/
	static void lookAt(const Vec3 &eye, const Vec3 &center, const Vec3 &up);

	/*Scale Camera from [-1;1]x[-1;1]x[0;1] to [x;x+w]x[y;y+h]x[0;1]*/
	static void setViewPort(int x, int y, int w, int h);

	/*Save scene in tga format file*/
	static bool compileScene(Scene * sc);
	
};


