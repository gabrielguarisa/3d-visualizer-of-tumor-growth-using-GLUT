#include "CellFactory.h"
#include "GlutWindow.h"

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

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

std::vector<Cell> cells;

int main(int argc, char** argv) {
	CellFactory factory("saida_anna.dat");
	cells = factory.fabricate();
	render = new ogl::Render(factory.max.x, factory.min.x, factory.max.y, factory.min.y);
	observer = Vector3(render->getMiddleX(), render->getMiddleY(), 900);

	ogl::GlutWindow window(argc, argv);

	window.start();

	return EXIT_SUCCESS;
}
