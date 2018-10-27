#ifndef SHADERINTERFACE_H
#define SHADERINTERFACE_H

#include "basicLibs.h"

class ShaderInterface
{
public:
	virtual ~ShaderInterface() = 0;

	virtual void attachTexture(int num, const char *name) = 0;

	virtual void attachViewMatrix(glm::mat4) = 0;

	virtual void attachProjectionMatrix(glm::mat4) = 0;

	virtual void attachModelMatrix(glm::mat4) = 0;

	virtual void use() = 0;
};

#endif // !SHADERINTERFACE_H