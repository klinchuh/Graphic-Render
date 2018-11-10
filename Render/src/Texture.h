#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

#include "basicLibs.h"

class Texture {
private:
	GLuint ID;
public:
	Texture() : ID(-1) { }

	//Load texture to memory(GPU?) from disk
	//Path - path to *.jpg file
	//Texture load only ones
	void load(GLuint num, const char *path);

	//Load texture to shader texture unit
	//num - number of unit (from 0 to 15)
	void bind(GLuint num);

	~Texture();
};

#endif // !TEXTURE_H
