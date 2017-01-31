#include <iostream>
#include "CellFactory.h"
#include "GlutWindow.h"
#include "FileList.h"

//Observer Position
Vector3 observer;

//Light Position
Vector3 light(320.0f, 228.0f, 500.0f);

//Mouse Movement
Vector3 rotation,
		rotIni,
		pos;

GLint	windowWidth = 500,
		windowHeight = 500;

GLint bpress;

ogl::Render *render;
ogl::Screenshot screenshot;

std::vector<CellFrame*> frames;
int frameNum = 0,
	automaticPlay = 0;

GLboolean lines = false;

extern GLfloat backgroundColor = 1.0f;

int main(int argc, char** argv) {
	std::vector<std::string> files = FileList::getFileNames("files/agentes/");

	frames = CellFactory::makeListFrames(files);

	render = new ogl::Render(frames[0]->getMin(), frames[0]->getMax());

	observer = Vector3(render->getMiddle().x, render->getMiddle().y, 900);

	ogl::GlutWindow window(argc, argv);

	window.start();

	return EXIT_SUCCESS;
}
