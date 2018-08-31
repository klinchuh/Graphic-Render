#pragma once
#include "tgaimage.h"
#include "scene.h"
#include "math.h"
#include "Matrix4.h"
#include "Matrix3.h"



//constants

//choose render with/without textures
const bool RENDER_WITHOUT_TEXTURES = 0;

//1 - make light more realistic, but take a slow
//0 - simplest type lighting 
const bool UPLIGHT = 1;

//{x, y, -z} - vector of light
const Vec3 LIGHT_VECTOR = {0., 0., 1.};

//chop off all with +z({0; +inf}) coord
const bool CHOP_OFF = 1;



//main class with most improtant functions
class Render
{
private:

	static const int sizeX = 1500, sizeY = 1500;

	static float zBuffer[sizeX * sizeY];

	static TGAImage resultImage;

	static Matrix4 perspectivViewMatrix, camViewMatrix;


	Render();
	~Render();

	/*1 - reset zBuffer
	2 - ...
	*/
	static void resetParam();

	//Drawing a line
	static void drawLine(int x0, int y0, int x1, int y1, TGAImage &im, const TGAColor &color);


	//Descript texture's point color
	static TGAColor getTextureColor(const TGAImage &intx, const Vec2 &vt0, const Vec2 &vt1, const Vec2 &vt2, bool second, float alpha, float beta, float zet);


	//The easyest method of drawing empty triangle
	static void drawEmpTriangle(std::vector <Vec3> lst, TGAImage &im);


	//Drawing a triangle with monotone color
	static void drawTriangle(Vec3 v1, Vec3 v2, Vec3 v3, const TGAColor &color, TGAImage &im);

	//Drawing a triangle with texture
	static void drawTriangleWT(Vec3 v0, Vec3 v1, Vec3 v2, Vec2 vt0, Vec2 vt1, Vec2 vt3, TGAImage &resultImage, const TGAImage & texture, float intensivity);

	//Get light Intensity of faces
	static float getPolLightIntensity(const Vec3 &a, const Vec3 &b, const Vec3 &c);

	//Rotate scene to currect(OZ to camera) position
	static void rotateToCameraView(std::vector <Vec3> &list);

public:
	//Preset Matrix for camera rotate
	//val - value of perpectiv veiw
	static void setCameraView(float val);

	//eye - the camera point
	//center - the point at which the camera is looking
	//up - up of camera
	static void lookAt(const Vec3 &eye, const Vec3 &center, const Vec3 &up);

	//Save scene in tga format file
	static bool compileSceneToFile(Scene * sc, const std::string &fileName);
	
};


