#include "stdafx.h"
#include "scene.h"
#include <iostream>


Scene::Scene() { }


Scene::~Scene() { }

bool Scene::loadScene(const std::string &fileName)
{
	std::ifstream is(fileName);
	std::string s;

	while (is >> s) {

		if (s == "#") {
			std::getline(is, s);
			continue;
		}

		if (s == "v") {
			float a, b, c;
			is >> a >> b >> c;
			vertex.push_back(Vec3{ a, b, c });
		}

		if (s == "vt") {
			float a, b, c;
			is >> a >> b >> c;
			textureVertex.push_back(Vec2(a, b));
		}

		if (s == "vn") {
			float a, b, c;
			is >> a >> b >> c;
			vertexNormals.push_back(Vec3(a, b, c));
		}

		if (s == "f") {
			polygons.push_back(Polygon(is));
		}

	}

	return true;
}

bool Scene::loadTexture(const std::string &fileName) {
	return sceneTexture.read_tga_file(fileName.c_str());
}
