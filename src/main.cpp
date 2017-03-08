#include <iostream>
#include "CellFactory.h"
#include "GlutWindow.h"
#include "FileList.h"
#include "GridFactory.h"

ConfigHandler* config;

//Observer Position
Vector3 observer;

//Light Position
Vector3 light(320.0f, 228.0f, 500.0f);

//Mouse Movement
Vector3 rotation = Vector3(),
		rotIni = Vector3(),
		pos = Vector3();

GLint bpress;

ogl::Render *render;
ogl::Screenshot screenshot;

std::vector<CellFrame*> frames;
int automaticPlay = 0;

int main(int argc, char** argv) {
	config = new ConfigHandler();
	if (!config->created())
		return EXIT_FAILURE;

	std::vector<std::string> agents = FileList::getFileNames(config->paths.agents);
	std::vector<std::string> nut = FileList::getFileNames(config->paths.nut);
	std::vector<std::string> egf = FileList::getFileNames(config->paths.egf);

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
