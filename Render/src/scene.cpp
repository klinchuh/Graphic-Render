#include "scene.h"
#include <iostream>
#include <sstream>

Scene::Scene(size_t texturesCount, size_t VAOsCount) {
	VAOs = new GLuint[VAOsCount];
	VAOsSizes = new size_t[VAOsCount];
	textures = new Texture[texturesCount];
}

Scene::~Scene() { }

bool Scene::loadVAO(size_t num, const char *fileName) {

	std::ifstream is(fileName);
	std::string s;

	std::vector <glm::vec3> spaceVertices;
	std::vector <glm::vec2> textureVertices;
	std::vector <glm::vec3> vertexNormals;

	std::vector <float> finalData;
	

	std::string str;
	
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

		
		if (s == "vn") {
			float a, b, c;
			is >> a >> b >> c;
			vertexNormals.push_back(glm::vec3(a, b, c));
		}
		
		if (s == "f") {
			int v1, v2, v3, vn1, vn2, vn3, vt1, vt2, vt3, v4, vt4, vn4;
			char trash;
			
			is >> v1 >> trash >> vt1 >> trash >> vn1 >> v2 >> trash >> vt2 >> trash >> vn2 >> v3 >> trash >> vt3 >> trash >> vn3;

			finalData.push_back(spaceVertices[v1 - 1][0]);
			finalData.push_back(spaceVertices[v1 - 1][1]);
			finalData.push_back(spaceVertices[v1 - 1][2]);
			finalData.push_back(textureVertices[vt1 - 1][0]);
			finalData.push_back(textureVertices[vt1 - 1][1]);
			finalData.push_back(vertexNormals[vn1 - 1][0]);
			finalData.push_back(vertexNormals[vn1 - 1][1]);
			finalData.push_back(vertexNormals[vn1 - 1][2]);

			finalData.push_back(spaceVertices[v2 - 1][0]);
			finalData.push_back(spaceVertices[v2 - 1][1]);
			finalData.push_back(spaceVertices[v2 - 1][2]);
			finalData.push_back(textureVertices[vt2 - 1][0]);
			finalData.push_back(textureVertices[vt2 - 1][1]);
			finalData.push_back(vertexNormals[vn2 - 1][0]);
			finalData.push_back(vertexNormals[vn2 - 1][1]);
			finalData.push_back(vertexNormals[vn2 - 1][2]);

			finalData.push_back(spaceVertices[v3 - 1][0]);
			finalData.push_back(spaceVertices[v3 - 1][1]);
			finalData.push_back(spaceVertices[v3 - 1][2]);
			finalData.push_back(textureVertices[vt3 - 1][0]);
			finalData.push_back(textureVertices[vt3 - 1][1]);
			finalData.push_back(vertexNormals[vn3 - 1][0]);
			finalData.push_back(vertexNormals[vn3 - 1][1]);
			finalData.push_back(vertexNormals[vn3 - 1][2]);


			//TO DO(èñïðàâèòü ãîâíîêîä)
			std::string str;

			std::getline(is, str);
			
			if (str.size() > 4) {
				std::stringstream ss;
				ss << str;
				ss >> v4 >> trash >> vt4 >> trash >> vn4;

				finalData.push_back(spaceVertices[v1 - 1][0]);
				finalData.push_back(spaceVertices[v1 - 1][1]);
				finalData.push_back(spaceVertices[v1 - 1][2]);
				finalData.push_back(textureVertices[vt1 - 1][0]);
				finalData.push_back(textureVertices[vt1 - 1][1]);
				finalData.push_back(vertexNormals[vn1 - 1][0]);
				finalData.push_back(vertexNormals[vn1 - 1][1]);
				finalData.push_back(vertexNormals[vn1 - 1][2]);

				finalData.push_back(spaceVertices[v3 - 1][0]);
				finalData.push_back(spaceVertices[v3 - 1][1]);
				finalData.push_back(spaceVertices[v3 - 1][2]);
				finalData.push_back(textureVertices[vt3 - 1][0]);
				finalData.push_back(textureVertices[vt3 - 1][1]);
				finalData.push_back(vertexNormals[vn3 - 1][0]);
				finalData.push_back(vertexNormals[vn3 - 1][1]);
				finalData.push_back(vertexNormals[vn3 - 1][2]);

				finalData.push_back(spaceVertices[v4 - 1][0]);
				finalData.push_back(spaceVertices[v4 - 1][1]);
				finalData.push_back(spaceVertices[v4 - 1][2]);
				finalData.push_back(textureVertices[vt4 - 1][0]);
				finalData.push_back(textureVertices[vt4 - 1][1]);
				finalData.push_back(vertexNormals[vn4 - 1][0]);
				finalData.push_back(vertexNormals[vn4 - 1][1]);
				finalData.push_back(vertexNormals[vn4 - 1][2]);
			}
			
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Set Atribut(VAOs) pointer ¹1 (texture coord)
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	//Set Atribut(VAOs) pointer ¹2 (normal vectors)
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	//Set up default Array Buffer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	VAOsSizes[num] = finalData.size() / 8;

	DEBUG_S(">>> Load VAO num=" << num);

	return true;
}


size_t Scene::addObject(size_t VAONum, size_t textureNum, glm::vec3 pos, glm::vec3 dir) {
	objects.push_back(Object{ VAONum, textureNum, pos, dir });
	DEBUG_S(">>> Add Object, current count: " << objects.size());
	return (int)objects.size() - 1;
}


void Scene::bindObject(size_t id) {
	glBindVertexArray(VAOs[objects[id].VAONum]);
	textures[objects[id].textureId].bind(0);
}


glm::mat4 Scene::getModelMatrix(size_t id) {
	glm::mat4 model;
	model = rotate(model, -objects[id].direction[0], { 0.0f, 0.0f, 1.0f });
	model = rotate(model, -objects[id].direction[1], { 0.0f, 1.0f, 0.0f });
	model = rotate(model, -objects[id].direction[2], { 1.0f, 0.0f, 0.0f });
	return glm::translate(glm::mat4(), objects[id].position) * model;
}

void Scene::loadTexture(size_t num, const char *path) {
	textures[num] = Texture();

	textures[num].bind(num);
	textures[num].load(num, path);
}
