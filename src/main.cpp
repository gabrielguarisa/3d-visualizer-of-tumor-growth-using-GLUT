#include <iostream>
#include "CellFactory.h"
#include "GlutWindow.h"
#include "FileList.h"

//Observer Position
Vector3 observer;

//Light Position
Vector3 light(320.0f, 228.0f, 500.0f);

//Mouse Movement
Vector3 rotation = Vector3(),
		rotIni = Vector3(),
		pos = Vector3();

GLint	windowWidth = 600,
		windowHeight = 600;

GLint bpress;

ogl::Render *render;
ogl::Screenshot screenshot;

std::vector<CellFrame*> frames;
int frameNum = 0,
	automaticPlay = 0;

GLboolean lines = false;

int main(int argc, char** argv) {
	std::vector<std::string> files = FileList::getFileNames("files/agentes/");

	frames = CellFactory::makeListFrames(files);

	render = new ogl::Render(Vector3(), frames[0]->domain);

	observer = frames[0]->domain;
	observer.z += 600;

	ogl::GlutWindow window(argc, argv);

	window.start();

	return EXIT_SUCCESS;
}
