#include <fstream>
#include <string>
#include <iostream>

#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode, fragmentCode;
	std::ifstream vertexFile, fragmentFile;



	//reading shaders from disk to memory
	try {
		//set up exceptions to streams
		vertexFile.exceptions(std::ios_base::failbit);
		fragmentFile.exceptions(std::ios_base::failbit);

		vertexFile.open(vertexPath, std::ios_base::binary);
		fragmentFile.open(fragmentPath, std::ios_base::binary);

		vertexFile.exceptions(0);
		fragmentFile.exceptions(0);
	}
	catch (std::ifstream::failure e)
	{
		ERROR_FLT("Can't find/open/read shader's files")
	}

	char c;

	while (vertexFile.good() && vertexFile.get(c)) {
		vertexCode.push_back(c);
	}

	while (fragmentFile.good() && fragmentFile.get(c)) {
		fragmentCode.push_back(c);
	}


	DEBUG_S(">>> loaded from disk vertex Shader:\n" << vertexCode << '\n'
		<< ">>> loaded from disk fragment Shader:\n" << fragmentCode);

	//transform shaders to char table
	const char *cVertexCode = vertexCode.c_str();
	const char *cFragmentCode = fragmentCode.c_str();


	//Compile vertex shader 
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, (&cVertexCode), NULL);
	glCompileShader(vertexShader);


	//check vertex shader on compilability
	checkCompileErrors(vertexShader, "vertex");


	//Compile fragment shader 
	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &cFragmentCode, NULL);
	glCompileShader(fragmentShader);


	//check fragment shader on compilability
	checkCompileErrors(fragmentShader, "fragment");


	//Link Program Shader(ID) from vertex and fragment shaders
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);


	//check vertex and fragment shaders on opportunity to link
	checkCompileErrors(ID, "link");

	//delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}


void Shader::checkCompileErrors(GLuint shader, const std::string &type) {
#ifdef DEBUG_LOG
	GLint success;
	GLchar infoLog[512];

	if (type == "link") {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);

		if (!success) {
			glGetProgramInfoLog(shader, 512, NULL, infoLog);
			ERROR_FLT("Linking shaders failed\n" << infoLog);
		}
		else {
			DEBUG_S(">>> Shaders have linked");
		}
	}
	else {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if (!success) {
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			ERROR_FLT("Can't compile fragment shader\n" << infoLog);
		}
		else {
			DEBUG_S(">>> " << type << " shader have compled");
		}
	}
#endif // !DEBUG_LOG
}


void Shader::use() const {
	glUseProgram(ID);
}


void Shader::attachViewMatrix(glm::mat4 viewMatrix) const {
	unsigned int transformLoc = glGetUniformLocation(ID, "view");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	//DEBUG_S("View matrix loaded");
}

void Shader::attachProjectionMatrix(glm::mat4 projectionMatrix) const {
	unsigned int transformLoc = glGetUniformLocation(ID, "projection");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	//DEBUG_S("projection matrix loaded");
}

void Shader::attachModelMatrix(glm::mat4 modelMatrix) const {
	unsigned int transformLoc = glGetUniformLocation(ID, "model");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	//DEBUG_S("model matrix loaded");
}