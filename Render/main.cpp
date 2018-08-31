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

	Render::lookAt(Vec3(7, 0, 7), Vec3(1.5, 0, 1.5), Vec3(0, 1, 0));

	Render::compileSceneToFile(mainScene, "output.tga");


	delete mainScene;
	return 0;
}