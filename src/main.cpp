#include <iostream>
#include "CellFactory.h"
#include "GlutWindow.h"
#include "FileList.h"
#include "GridFactory.h"

ConfigHandler* config;

Grid 	nutGrids,
		egfGrids;

ogl::Render *render;

std::vector<CellFrame*> frames;

int main(int argc, char** argv) {
	config = new ConfigHandler();

	if (!config->created())
		return EXIT_FAILURE;

	frames = CellFactory::makeListFrames(FileList::getFileNames(config->paths.agents));
	nutGrids = GridFactory::makeListGrids(FileList::getFileNames(config->paths.nut), frames[0]->domain, 10);
	egfGrids = GridFactory::makeListGrids(FileList::getFileNames(config->paths.egf), frames[0]->domain, 10);

	config->display.lines.maximumLimit = Vector3(frames[0]->domain.x + config->display.lines.cellGap, frames[0]->domain.y + config->display.lines.cellGap, frames[0]->domain.z);
	config->display.lines.minimumLimit = Vector3(-config->display.lines.cellGap, -config->display.lines.cellGap, 0);

	ogl::GlutWindow window(argc, argv);

	window.start();

	return EXIT_SUCCESS;
}
