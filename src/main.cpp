#include <iostream>
#include "CellFactory.h"
#include "GlutWindow.h"
#include "FileList.h"
#include "GridFactory.h"

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

std::vector<std::vector<std::vector<std::vector<double> > > > nutGrids;
std::vector<std::vector<std::vector<std::vector<double> > > > egfGrids;
std::vector<CellFrame*> frames;
int frameNum = 0,
	automaticPlay = 0;

GLboolean lines = false;

int main(int argc, char** argv) {
	std::vector<std::string> agents = FileList::getFileNames("files/agentes/");
	std::vector<std::string> nut = FileList::getFileNames("files/nut/");
	std::vector<std::string> egf = FileList::getFileNames("files/egf/");

	frames = CellFactory::makeListFrames(agents);

	nutGrids = GridFactory::makeListGrids(nut, frames[0]->domain, 10);
	egfGrids = GridFactory::makeListGrids(egf, frames[0]->domain, 10);

	render = new ogl::Render(Vector3(), frames[0]->domain);

	observer = frames[0]->domain;
	observer.z += 600;

	ogl::GlutWindow window(argc, argv);

	window.start();

	return EXIT_SUCCESS;
}
