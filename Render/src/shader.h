#ifndef SHADER_H
#define SHADER_H

#include "basicLibs.h"

#include "shaderInterface.h"

class Shader : public ShaderInterface {
private:
	//our shader identificator
	GLuint ID;

public:

	Shader(): ID(0) { }

	//Compile and link vertex and fragment shaders
	//vertexPath - path to vertex shader
	//fragmentPath  - path to fragment shader
	Shader(const char* vertexPath, const char* fragmentPath);

	//link GL_TEXTURE(NUM)(texture unit) and uniform sampler2D in fragment shader
	//name - имя переменной в шейдоре
	//num - номер юнита
	void attachTexture(int num, const char *name) const {
		glUniform1i(glGetUniformLocation(ID, name), num);
	}

	void setVec3(const char *name, glm::vec3 vec) {
		glUniform3f(glGetUniformLocation(ID, name), vec[0], vec[1], vec[2]);
	}

	//load View matrix in shader
	void attachViewMatrix(glm::mat4*) const;

	//load projection(perspectiv view) matrix in shader
	void attachProjectionMatrix(glm::mat4*) const;

	//load model matrix in shader
	void attachModelMatrix(glm::mat4*) const;

	//Bind our shader as current
	void use() const;

	//return ID
	GLuint getId() {
		return ID;
	}

private:
	//Check compile procces on errors
	//shader - shader
	//shader - type of shader(vertex/fragment) or link(for check linking process)
	static void checkCompileErrors(GLuint shader, const std::string &type);
};

#endif 
