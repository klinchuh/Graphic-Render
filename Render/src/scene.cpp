#include "scene.h"
#include <iostream>
#include <sstream>


Scene::Scene(int texturesCount, int VAOsCount) {
	VAOs = new GLuint[VAOsCount];
	size = new int[VAOsCount];
	textures = new Texture[texturesCount];
}


Scene::~Scene() { }


bool Scene::loadVAO(int num, const char *fileName) {

	std::ifstream is(fileName);
	std::string s;

	std::vector <glm::vec3> spaceVertices;
	std::vector <glm::vec2> textureVertices;

	std::vector <float> finalData;

	while (is >> s) {

		if (s[0] == '#') {
			std::getline(is, s);
			continue;
		}

		if (s == "v") {
			float a, b, c;
			is >> a >> b >> c;
			spaceVertices.push_back(glm::vec3{ a, b, c });
		}

		if (s == "vt") {
			std::string s;
			getline(is, s);
			std::stringstream ss;
			ss << s;
			float a, b, c;
			ss >> a >> b >> c;
			textureVertices.push_back(glm::vec2(a, b));
		}

		//Vertex normal, TODO
		/*if (s == "vn") {

			float a, b, c;
			is >> a >> b >> c;
			vertexNormals.push_back(Vec3(a, b, c));
		}*/

		if (s == "f") {
			int v1, v2, v3, vn1, vn2, vn3, vt1, vt2, vt3;
			char trash;
			is >> v1 >> trash >> vt1 >> trash >> vn1 >> v2 >> trash >> vt2 >> trash >> vn2 >> v3 >> trash >> vt3 >> trash >> vn3;
			finalData.push_back(spaceVertices[v1 - 1][0]);
			finalData.push_back(spaceVertices[v1 - 1][1]);
			finalData.push_back(spaceVertices[v1 - 1][2]);
			finalData.push_back(textureVertices[vt1 - 1][0]);
			finalData.push_back(textureVertices[vt1 - 1][1]);
			finalData.push_back(spaceVertices[v2 - 1][0]);
			finalData.push_back(spaceVertices[v2 - 1][1]);
			finalData.push_back(spaceVertices[v2 - 1][2]);
			finalData.push_back(textureVertices[vt2 - 1][0]);
			finalData.push_back(textureVertices[vt2 - 1][1]);
			finalData.push_back(spaceVertices[v3 - 1][0]);
			finalData.push_back(spaceVertices[v3 - 1][1]);
			finalData.push_back(spaceVertices[v3 - 1][2]);
			finalData.push_back(textureVertices[vt3 - 1][0]);
			finalData.push_back(textureVertices[vt3 - 1][1]);
		}

	}

	//Init Array Buffer to set up VAO
	glGenVertexArrays(1, &VAOs[num]);
	glBindVertexArray(VAOs[num]);

	//load VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * finalData.size(), &finalData[0], GL_STATIC_DRAW);

	//load EBO
	//glGenBuffers(1, &EBOs[0]);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//Set Atribut(VAOs) pointer ¹0 (vertex)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Set Atribut(VAOs) pointer ¹1 (texture coord)
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Set up default Array Buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	size[num] = finalData.size() / 5;

	return true;
}


void Scene::loadTexture(int num, const char *path) {
	textures[num] = Texture();

	textures[num].load(path);
	textures[num].loadToUnit(num);
}
