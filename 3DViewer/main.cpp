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
ogl::Screenshot screenshot;

std::vector<Cell> cells;

std::vector<Cell> temp; //remove
bool trueRender = true; //remove
GLboolean lines = false;

int main(int argc, char** argv) {
	CellFactory factory("saida_anna.dat");
	cells = factory.fabricate();
	temp = factory.simulate3D(); //remove
	render = new ogl::Render(factory.min, factory.max);

	observer = Vector3(render->getMiddle().x, render->getMiddle().y, 900);

	ogl::GlutWindow window(argc, argv);

	window.start();

	return EXIT_SUCCESS;
}
