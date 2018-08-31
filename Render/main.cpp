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

	Render::lookAt(Vec3(12, 0, 6), Vec3(2, 0, 1), Vec3(0, 1, 0));

	Render::compileSceneToFile(mainScene, "output.tga");


	delete mainScene;
	return 0;
}