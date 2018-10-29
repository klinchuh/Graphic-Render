#include "scene.h"
#include <iostream>
#include <sstream>


Scene::Scene(int texturesCount, int VAOsCount) {
	VAOs = new GLuint[VAOsCount];
	textures = new Texture[texturesCount];
}

Scene::~Scene() { }


bool Scene::loadVAO(int num, const char *fileName) {

	std::ifstream is(fileName);
	std::string s;

	/*while (is >> s) {

		if (s[0] == '#') {
			std::getline(is, s);
			continue;
		}

		if (s == "v") {
			float a, b, c;
			is >> a >> b >> c;
			vertex.push_back(glm::vec3{ a, b, c });
		}

		if (s == "vt") {
			std::string s;
			getline(is, s);
			std::stringstream ss;
			ss << s;
			float a, b, c;
			ss >> a >> b >> c;
			textureVertex.push_back(Vec2(a, b));
		}

		//Vertex normal, TODO
		/*if (s == "vn") {

			float a, b, c;
			is >> a >> b >> c;
			vertexNormals.push_back(Vec3(a, b, c));
		}

		if (s == "f") {
			int v1, v2, v3, vn1, vn2, vn3, vt1, vt2, vt3;
			char trash;
			is >> v1 >> trash >> vt1 >> trash >> vn1 >> v2 >> trash >> vt2 >> trash >> vn2 >> v3 >> trash >> vt3 >> trash >> vn3;
			vertex[0] = v1 - 1;
			vertex[1] = v2 - 1;
			vertex[2] = v3 - 1;
			normal[0] = vn1 - 1;
			normal[1] = vn2 - 1;
			normal[2] = vn3 - 1;
			texture[0] = vt1 - 1;
			texture[1] = vt2 - 1;
			texture[2] = vt3 - 1;
			polygons.push_back(Polygon3(is));
		}

	}
*/
	return true;
}


void Scene::loadTexture(int num, const char *path) {
	textures[num] = Texture();

	textures[num].load(path);
	textures[num].loadToUnit(num);
}
