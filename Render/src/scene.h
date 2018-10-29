#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <fstream>
#include <string>

#include "basicLibs.h"

#include "Texture.h"


//struct for containing main data of scene
class Scene
{
public:
	Texture *textures;
	GLuint *VAOs, *VBO, *EBOs;

	//can't load more VAOs or Texture than 
	//texturesCount - reserve of textures
	//VAOsCount - reserve of VAOs
	Scene(int texturesCount = 1, int VAOsCount = 1);

	~Scene();

	//load VAO from *.obj file
	//num - number of object
	//fileName - path to *.obj file
	bool loadVAO(int num, const char *fileName);

	//load texture from file to texture(num) unit
	//num - number of texture unit
	//fileName - path to texture file
	void loadTexture(int num, const char *fileName);
};

#endif // !SCENE_H