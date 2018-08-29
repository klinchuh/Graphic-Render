#pragma once
#include "tgaimage.h"
#include "scene.h"
#include "math.h"



//constants

//choose render with/without textures
const bool RENDER_WITHOUT_TEXTURES = 0;

//1 - make light more realistic, but take a slow
//0 - simplest type lighting 
const bool UPLIGHT = 1;

//{x, y, -z} - vector of light
const Vec3 LIGHT_VECTOR = {0., 0., 1.};





//main class with most improtant functions
class Render
{
private:

	static const int sizeX = 1500, sizeY = 1500;

	static float zBuffer[sizeX * sizeY];

	static TGAImage resultImage;

	Render();
	~Render();


	//Drawing a line
	static void drawLine(int x0, int y0, int x1, int y1, TGAImage &im, const TGAColor &color);


	//Descript texture's point color
	static TGAColor getTextureColor(const TGAImage &intx, const Vec2 &vt0, const Vec2 &vt1, const Vec2 &vt2, bool second, float alpha, float beta, float zet, bool sw);


	//The easyest method of drawing empty triangle
	static void drawEmpTriangle(std::vector <Vec3> lst, TGAImage &im);


	//Drawing a triangle with monotone color
	static void drawTriangle(Vec3 v1, Vec3 v2, Vec3 v3, const TGAColor &color, TGAImage &im);

	//Drawing a triangle with texture
	static void drawTriangleWT(Vec3 v0, Vec3 v1, Vec3 v2, Vec2 vt0, Vec2 vt1, Vec2 vt3, TGAImage &resultImage, const TGAImage & texture, float intensivity);

public:
	//Save scene in tga format file
	static bool compileSceneToFile(Scene * sc, const std::string &fileName);
	
};


