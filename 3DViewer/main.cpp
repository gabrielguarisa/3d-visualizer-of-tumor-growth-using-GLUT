#include "CellFactory.h"
#include "OGL.h"

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

//Observer Position
Vector3 observer, obsini;

//Light Position
Vector3 light(320.0f, 228.0f, 500.0f);

//Mouse Movement
Vector3 rotation,
		rotIni,
		pos;

GLint	windowWidth = 500,
		windowHeight = 500;

GLint bpress;

std::vector<Cell> cells;


int main(int argc, char** argv) {
	CellFactory factory("saida_anna.dat");
	cells = factory.fabricate();

	observer = obsini = Vector3((factory.min.x + factory.max.x) / 2, (factory.min.y + factory.max.y) / 2, 900);

	ogl::GlutWindow window(argc, argv);

	window.start();

	return EXIT_SUCCESS;
}
