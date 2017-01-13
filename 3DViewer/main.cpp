#include "CellFactory.h"
#include "GlutWindow.h"
#include "FileReader.h"
#include <iostream>

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

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
int frameNum = 0;

GLboolean lines = false;

int main(int argc, char** argv) {
	FileReader reader;
	CellFactory factory;

	for (int i = 2; i < reader.result.size(); i++)
	{
		std::cout << reader.result[i] << std::endl;
		frames.push_back(factory.fabricate(reader.result[i]));
	}

	//frames.push_back(factory.fabricate("files/saida0-00400.dat"));

	render = new ogl::Render(frames[0]->getMin(), frames[0]->getMax());

	observer = Vector3(render->getMiddle().x, render->getMiddle().y, 900);

	ogl::GlutWindow window(argc, argv);

	window.start();

	return EXIT_SUCCESS;
}
