#include "stdafx.h"
#include "Render.h"
#include <cassert>
#include <algorithm>
#include <iostream>

//int Render::sizeX = 1500;
//int Render::sizeY = 1500;
TGAImage Render::resultImage;

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

float Render::zBuffer[sizeX * sizeY];

Render::Render() { exit(2); }

Render::~Render() { }

void Render::drawLine(int x0, int y0, int x1, int y1, TGAImage &im, const TGAColor &color) {
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



void Render::drawEmpTriangle(std::vector <Vec3> lst, TGAImage &im) {

	assert(lst.size() == 3);

	for (int i = 0; i < 3; i++) {
		int x0 = (int)((lst[i].x + 1.) * (double)sizeX / 2.);
		int y0 = (int)((lst[i].y + 1.) * (double)sizeY / 2.);
		int x1 = (int)((lst[(i + 1) % 3].x + 1.) * (double)sizeX / 2.);
		int y1 = (int)((lst[(i + 1) % 3].y + 1.) * (double)sizeY / 2.);
		drawLine(x0, y0, x1, y1, im, white);
	}
}



void Render::drawTriangle(Vec3 v0, Vec3 v1, Vec3 v2, const TGAColor & color, TGAImage & resultImage)
{
	//Refactoring must be in both drawing triangle functions
	if (v0.y > v1.y) std::swap(v0, v1);
	if (v1.y > v2.y) std::swap(v1, v2);
	if (v0.y > v1.y) std::swap(v0, v1);

	float totalHight = (int)((v2.y + 1.) * (float)sizeY / 2.) - (int)((v0.y + 1.) * (float)sizeY / 2.);
	float firstHigth = (int)((v1.y + 1.) * (float)sizeY / 2.) - (int)((v0.y + 1.) * (float)sizeY / 2.);
	float secondHigth = (int)((v2.y + 1.) * (float)sizeY / 2.) - (int)((v1.y + 1.) * (float)sizeY / 2.);
	
	for (int i = 0; i < totalHight; i++) {
		bool second = false;

		if ((float)i >= firstHigth) {
			second = true;
		}

		float alpha = (float)i / totalHight;

		float beta = 0;
		if (second) {
			if (secondHigth == 0) continue;
			beta = (i - firstHigth) / secondHigth;
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

		int x0 = (a.x + 1.) * (float)sizeX / 2.;	
		int x1 = (b.x + 1.) * (float)sizeX / 2.;
		if (x0 > x1) std::swap(x0, x1);

		for (int j = x0; j <= x1; j++) {
			float zet = (x0 == x1 ? (float)1 : ((float)(j - x0) / (float)(x1 - x0)));
			Vec3 temp = a + zet * (b - a);
			if (temp.z > zBuffer[j * sizeY + i + (int)((v0.y + 1.) * (float)sizeY / 2.)]) {
				resultImage.set(j, i + (int)((v0.y + 1.) * (float)sizeY / 2.), color);
				zBuffer[j * sizeY + i + (int)((v0.y + 1.) * (float)sizeY / 2.)] = temp.z;
			}
		}
	}
}


void Render::drawTriangleWT(Vec3 v0, Vec3 v1, Vec3 v2, Vec2 vt0, Vec2 vt1, Vec2 vt2, TGAImage & resultImage, const TGAImage &texture, float intensity)
{
	//Refactoring must be in both drawing triangle functions
	if (v0.y > v1.y) std::swap(v0, v1), std::swap(vt0, vt1);
	if (v1.y > v2.y) std::swap(v1, v2), std::swap(vt1, vt2);
	if (v0.y > v1.y) std::swap(v0, v1), std::swap(vt0, vt1);

	float totalHight = (int)((v2.y + 1.) * (float)sizeY / 2.) - (int)((v0.y + 1.) * (float)sizeY / 2.);
	float firstHigth = (int)((v1.y + 1.) * (float)sizeY / 2.) - (int)((v0.y + 1.) * (float)sizeY / 2.);
	float secondHigth = (int)((v2.y + 1.) * (float)sizeY / 2.) - (int)((v1.y + 1.) * (float)sizeY / 2.);

	for (int i = 0; i < totalHight; i++) {
		bool second = false;
		if ((float)i >= firstHigth) {
			second = true;
		}

		float alpha = (float)i / totalHight;
		float beta = 0;
		if (second) {
			if (secondHigth == 0) continue;
			beta = (i - firstHigth) / secondHigth;
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

		int x0 = (a.x + 1.) * (float)sizeX / 2.;
		int x1 = (b.x + 1.) * (float)sizeX / 2.;
		bool sw = 0;
		if (x0 > x1) std::swap(x0, x1), sw = true;

		for (int j = x0; j <= x1; j++) {
			float zet = (x0 == x1 ? (float)1 : ((float)(j - x0) / (float)(x1 - x0)));
			Vec3 temp = a +  zet * (b - a);
			if (temp.z > zBuffer[j * sizeY + i + (int)((v0.y + 1.) * (float)sizeY / 2.)]) {
				TGAColor color = getTextureColor(texture, vt0, vt1, vt2, second, alpha, beta, zet, sw);
				color.b *= intensity;
				color.r *= intensity;
				color.g *= intensity;
				resultImage.set(j, i + (int)((v0.y + 1.) * (float)sizeY / 2.), color);
				zBuffer[j * sizeY + i + (int)((v0.y + 1.) * (float)sizeY / 2.)] = temp.z;
			}
		}
	}
}


TGAColor Render::getTextureColor(const TGAImage &intx, const Vec2 &vt0, const Vec2 &vt1, const Vec2 &vt2,
	                                              bool second, float alpha, float beta, float zet, bool sw) {
	Vec2 left, right, middle;
	if (second) {
		left = (1 - alpha) * vt0 + alpha * vt2;
		right = (1 - beta) * vt1 + beta * vt2;
	} else {
		left = (1 - alpha) * vt0 + alpha * vt2;
		right = (1 - beta) * vt0 + beta * vt1;
	}
	if (sw == 0) {
		middle = (1 - zet) * left + zet * right;
	}
	else {
		middle = (1 - zet) * right + zet * left;
	}
	int textSizeX = intx.get_width();
	int textSizeY = intx.get_height();
	return intx.get(textSizeX * middle.x, textSizeY * (1 - middle.y));
}


bool Render::compileSceneToFile(Scene *sc, const std::string &fileName)
{
	for (int i = 0; i < sizeX * sizeY; i++) {
		zBuffer[i] = INT32_MIN;
	}

	resultImage = TGAImage(sizeX, sizeY, TGAImage::RGB);

	for (const auto &x : sc->polygons) {
		float shadeIntensity;

		Vec3 normal = crossPrt(sc->vertex[x.vertex[1]] - sc->vertex[x.vertex[0]], sc->vertex[x.vertex[2]] - sc->vertex[x.vertex[0]]);

		normal = normalize(normal);

		shadeIntensity = scalarPrt3(normalize(Vec3(LIGHT_VECTOR)), normal);

		//if (shadeIntensity < 0) continue;

		shadeIntensity = std::max(shadeIntensity, (float)0.2);


		if (UPLIGHT) {
			shadeIntensity = sqrt(shadeIntensity);
		}

		if (RENDER_WITHOUT_TEXTURES) {
			TGAColor color = TGAColor(255 * shadeIntensity, 255 * shadeIntensity, 255 * shadeIntensity, 255);

			drawTriangle(sc->vertex[x.vertex[0]], sc->vertex[x.vertex[1]], sc->vertex[x.vertex[2]], color, resultImage);
		}
		else {
			drawTriangleWT(sc->vertex[x.vertex[0]], sc->vertex[x.vertex[1]], sc->vertex[x.vertex[2]], 
				sc->textureVertex[x.texture[0]], sc->textureVertex[x.texture[1]], sc->textureVertex[x.texture[2]],
				resultImage, sc->sceneTexture, shadeIntensity);

		}
	}

	resultImage.flip_vertically();
	resultImage.write_tga_file(fileName.c_str());

	return false;
}


