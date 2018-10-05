#pragma once
#include "points.h"
#include <vector>
#include <fstream>
#include <string>
#include "tgaimage.h"


//struct for containing main data of scene
struct Scene
{
	std::vector <Vec3> vertex;
	std::vector <Polygon3> polygons;
	std::vector <Vec2> textureVertex;
	std::vector <Vec3> vertexNormals;

	TGAImage sceneTexture;

	Scene();

	~Scene();

	bool loadScene(const std::string &fileName);

	bool loadTexture(const std::string &fileName);


	void clearSc() {
		vertex.clear();
		polygons.clear();
		textureVertex.clear();
		vertexNormals.clear();
	}


	void clearTx() {
		sceneTexture.clear();
	}
};
