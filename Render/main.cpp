#include "stdafx.h"
#include "tgaimage.h"
#include "scene.h"
#include "Render.h"
#include <iostream>
#include <cassert>



int main(int argc, char** argv) {

	Scene *mainScene = new Scene();

	assert(mainScene->loadScene("african_head.obj"));
	assert(mainScene->loadTexture("african_head_diffuse.tga"));

	Render::compileSceneToFile(mainScene, "output.tga");


	delete mainScene;
	return 0;
}