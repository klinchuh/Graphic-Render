#ifndef SHADERINTERFACE_H
#define SHADERINTERFACE_H

#include "basicLibs.h"

class ShaderInterface
{
public:
	virtual void attachTexture(int , const char *) const = 0;

	virtual void attachViewMatrix(glm::mat4*) const = 0;

	virtual void attachProjectionMatrix(glm::mat4*) const = 0;

	virtual void attachModelMatrix(glm::mat4*) const = 0;

	virtual void use() const = 0;
};

#endif // !SHADERINTERFACE_H