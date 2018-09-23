#include "Render.h"
#include <cassert>
#include <algorithm>
#include <windows.h>
#include <iostream>
#include <vector>

//const int Render::sizeX = 700, sizeY = 700;
const float Render::ZBUFFERDEEP = 1.;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

Matrix4 Render::perspectivViewMatrix, Render::camViewMatrix, Render::viewPort;

float Render::zBuffer[sizeX * sizeY];
int Render::colorBuffer[sizeX * sizeY];

bool Render::RENDER_WITHOUT_TEXTURES = 0;

//------------------------------------------------------------------------------------
Render::Render() { exit(2); }
//------------------------------------------------------------------------------------
Render::~Render() { }
//------------------------------------------------------------------------------------
void Render::drawLine(int x0, int y0, int x1, int y1,
	TGAImage &im, const TGAColor &color) {
	double error = 0, s;
	int q = 0;

	if (x0 > x1) {
		std::swap(x0, x1);
		std::swap(y0, y1);
	}
	if (y0 < y1)
		q = 1;
	else
		q = -1;
	s = abs((double)(y1 - y0) / (double)(x1 - x0));
	for (int i = x0; i <= x1; i++) {
		if (error >= 1.) {
			y0 += q;
			im.set(i, y0, color);
			error -= 1;
			if (error >= 1.) {
				i--;
				continue;
			}
			else {
				error += s;
			}
		}
		else {
			error += s;
			im.set(i, y0, color);
		}
	}
}
//------------------------------------------------------------------------------------
void Render::drawEmpTriangle(std::vector <Vec3> lst, TGAImage &im) {

	assert(lst.size() == 3);

	for (int i = 0; i < 3; i++) {
		int x0 = (int)((lst[i][0] + 1.) * (double)sizeX / 2.);
		int y0 = (int)((lst[i][0] + 1.) * (double)sizeY / 2.);
		int x1 = (int)((lst[(i + 1) % 3][0] + 1.) * (double)sizeX / 2.);
		int y1 = (int)((lst[(i + 1) % 3][1] + 1.) * (double)sizeY / 2.);
		drawLine(x0, y0, x1, y1, im, white);
	}
}
//------------------------------------------------------------------------------------
float getGouraudShadeIntesity(const Vec3 &vn0, const Vec3 &vn1, const Vec3 &vn2,
	bool second, float alpha, float beta, float zet)
{
	Vec3 left, right, middle;
	if (second) {
		left = (1. - alpha) * vn0 + alpha * vn2;
		right = (1. - beta) * vn1 + beta * vn2;
	}
	else {
		left = (1. - alpha) * vn0 + alpha * vn2;
		right = (1. - beta) * vn0 + beta * vn1;
	}

	middle = (1. - zet) * left + zet * right;
	return max(Math::scalarPrt3(middle, LIGHT_VECTOR), (float)0.);
}
//------------------------------------------------------------------------------------
void Render::drawTriangleWT(Vec3 v0, Vec3 v1, Vec3 v2, 
	Vec2 vt0, Vec2 vt1, Vec2 vt2, 
	Vec3 vn0, Vec3 vn1, Vec3 vn2, const TGAImage &texture)
{
	if (v0[1] > v1[1]) std::swap(v0, v1), std::swap(vt0, vt1), std::swap(vn0, vn1);
	if (v1[1] > v2[1]) std::swap(v1, v2), std::swap(vt1, vt2), std::swap(vn1, vn2);
	if (v0[1] > v1[1]) std::swap(v0, v1), std::swap(vt0, vt1), std::swap(vn0, vn1);

	float totalHight = v2[1] - v0[1];
	float firstHigth = v1[1] - v0[1];
	float secondHigth = v2[1] - v1[1];// v2[1] - v1[1];

	for (int i = 0; i < totalHight; i++) {
		bool second = false;
		if ((float)i >= firstHigth) {
			second = true;
		}

		float alpha = (float)i / totalHight;
		float beta = 0;
		if (second) {
			if (secondHigth == 0) continue;
			beta = ((float)i - firstHigth) / secondHigth;
		}
		else {
			if (firstHigth == 0) continue;
			beta = (float)i / firstHigth;
		}

		Vec3 a = v0 + alpha * (v2 - v0);
		Vec3 b;
		if (second) {
			b = v1 + beta * (v2 - v1);
		}
		else {
			b = v0 + beta * (v1 - v0);
		}

		int x0 = a[0];
		int x1 = b[0];
		bool swaped = 0;
		if (x0 > x1) std::swap(x0, x1), swaped = true;

		for (int j = x0; j <= x1; j++) {

			if (i > sizeY || i < 0 || j > sizeX || j < 0) continue;

			float zet = (x0 == x1 ? (float)1 : ((float)(j - x0) / (float)(x1 - x0)));
			Vec3 temp = a +  zet * (b - a);
			if (temp[2] > zBuffer[j * sizeY + i + (int)v0[1]]) {
				if (swaped == 1) {
					zet = 1. - zet;
				}

				TGAColor color;
				float intensity = (float)1.;

				if (RENDER_WITHOUT_TEXTURES) {
					color = TGAColor(255, 255, 255, 255);
				} else {
					color = getTextureColor(texture, vt0, vt1, vt2, second, alpha, beta, zet);
				}

				intensity = getGouraudShadeIntesity(vn0, vn1, vn2, second, alpha, beta, zet);

				color.b *= intensity;
				color.r *= intensity;
				color.g *= intensity;

				colorBuffer[j * sizeY + i + (int)v0[1]] = RGB(color.r, color.g, color.b);

				zBuffer[j * sizeY + i + (int)v0[1]] = temp[2];
			}
		}
	}
}
//------------------------------------------------------------------------------------
void Render::resetParam()
{
	for (int i = 0; i < sizeX * sizeY; i++) {
		zBuffer[i] = INT32_MIN;
	}

	for (int i = 0; i < sizeX * sizeY; i++) {
		colorBuffer[i] = RGB(0, 200, 0);
	}
}
//------------------------------------------------------------------------------------
TGAColor Render::getTextureColor(const TGAImage &intx,
	const Vec2 &vt0, const Vec2 &vt1, const Vec2 &vt2, 
	bool second, float alpha, float beta, float zet) {

	Vec2 left, right, middle;
	if (second) {
		left = (1. - alpha) * vt0 + alpha * vt2;
		right = (1. - beta) * vt1 + beta * vt2;
	} else {
		left = (1. - alpha) * vt0 + alpha * vt2;
		right = (1. - beta) * vt0 + beta * vt1;
	}

	middle = (1. - zet) * left + zet * right;

	int textSizeX = intx.get_width();
	int textSizeY = intx.get_height();
	return intx.get(textSizeX * middle[0], textSizeY * (1 - middle[1]));
}
//------------------------------------------------------------------------------------
float Render::getPolLightIntensity(const Vec3 &a, const Vec3 &b, const Vec3 &c) {

	float answer;

	Vec3 normal = Math::crossPrt(b - a, c - a);

	normal = Math::normalize(normal);

	answer = Math::scalarPrt3(Math::normalize(LIGHT_VECTOR), normal);

	if (answer < 0) return 0;

	//answer = std::max(answer, (float)0.2);

	return answer;
}
//------------------------------------------------------------------------------------
void Render::setCameraView(float val) {
	perspectivViewMatrix.setIdentityMatrix();
	perspectivViewMatrix[3][2] = -1. / val;
}
//------------------------------------------------------------------------------------
void Render::transformToDisplayCoord(std::vector <Vec3> &list) {

	//very important Order of matrices 
	Matrix4 finiteMatrix = viewPort * perspectivViewMatrix * camViewMatrix;

	for (int i = 0; i < list.size(); i++) {
		Vec4 tmp = Vec4(list[i][0], list[i][1], list[i][2], 1);
		tmp = finiteMatrix * tmp;
		list[i] = Vec3::project4To3(tmp);
		list[i][0] = (int)list[i][0];
		list[i][1] = (int)list[i][1];
	}
}
//------------------------------------------------------------------------------------
void Render::lookAt(const Vec3 &eye, const Vec3 &center, const Vec3 &up) {

	Render::setCameraView(Math::_length(eye - center));

	Vec3 z = Math::normalize(eye - center);
	Vec3 x = Math::normalize(Math::crossPrt(up, z));
	Vec3 y = Math::normalize(Math::crossPrt(z, x));
	Matrix4 Minv;
	Matrix4 Tr;
	Tr.setIdentityMatrix();
	Minv.setIdentityMatrix();
	for (int i = 0; i < 3; i++) {
		Minv[0][i] = x[i];
		Minv[1][i] = y[i];
		Minv[2][i] = z[i];
		Tr[i][3] = -center[i];
	}
	camViewMatrix = Minv * Tr;
}
//------------------------------------------------------------------------------------
bool Render::compileScene(Scene *sc)
{
	resetParam();

	for (const auto &x : sc->polygons) {

		std::vector <Vec3> listOfVertex = { sc->vertex[x.vertex[0]] , sc->vertex[x.vertex[1]], sc->vertex[x.vertex[2]] };
		std::vector <Vec2> listOfTecturs = { sc->textureVertex[x.texture[0]] , sc->textureVertex[x.texture[1]], sc->textureVertex[x.texture[2]] };
		std::vector <Vec3> listOfNormals = { sc->vertexNormals[x.normal[0]] , sc->vertexNormals[x.normal[1]], sc->vertexNormals[x.normal[2]] };

		transformToDisplayCoord(listOfVertex);

		drawTriangleWT(listOfVertex[0], listOfVertex[1], listOfVertex[2],
			listOfTecturs[0], listOfTecturs[1], listOfTecturs[2],
			listOfNormals[0], listOfNormals[1], listOfNormals[2],
			sc->sceneTexture);

	}

	return false;
}
//------------------------------------------------------------------------------------
void Render::setCameraScale(int x, int y, int w, int h) {
	viewPort.setIdentityMatrix();
	viewPort[0][3] = x + w / 2.f;
	viewPort[1][3] = y + h / 2.f;
	viewPort[2][3] = ZBUFFERDEEP / 2.f;

	viewPort[0][0] = w / 2.f;
	viewPort[1][1] = h / 2.f;
	viewPort[2][2] = ZBUFFERDEEP / 2.f;
}
//------------------------------------------------------------------------------------
