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
	struct Object {
		size_t VAONum, textureId;
		glm::vec3 position, direction;
	};

	Texture *textures;
	GLuint *VAOs, VBO, *EBOs;
	std::vector<Object> objects;

	//Pos and dir of VAOs(object's)
	size_t *VAOsSizes;

public:
	//can't load more VAOs or Texture than 
	//texturesCount - reserve of textures
	//VAOsCount - reserve of VAOs
	Scene(size_t texturesCount = 1, size_t VAOsCount = 1);

	~Scene();

	//load VAO from *.obj file
	//num - number of object
	//fileName - path to *.obj file
	bool loadVAO(size_t num, const char *fileName);

	//Add Object
	// VAONum - number of object's mesh
	// textureNum - number of texture unit
	// pos - position of object in space
	// dir - roll/yaw/pitch of object;
	// return id of object aka cuurent count of objects - 1
	size_t addObject(size_t VAONum, size_t textureNum, glm::vec3 pos, glm::vec3 dir);

	//Bint object's VAO(Mesh) and texture
	//id - Id of object
	void bindObject(size_t id);

	//return model Matrix to object
	//id = id of object
	glm::mat4 getModelMatrix(size_t id);

	//return count of verteces in VAO
	//num - number of VAO
	size_t getObjectMeshSize(size_t num) {
		return VAOsSizes[objects[num].VAONum];
	}

	//return count of objects
	size_t getObjectsCount() {
		return objects.size();
	}

	int getObjectTextureUnit(size_t id) {
		return objects[id].textureId;
	}

	//load texture from file to texture(num) unit
	//num - number of texture unit
	//fileName - path to texture file
	void loadTexture(size_t num, const char *fileName);
};

#endif // !SCENE_H