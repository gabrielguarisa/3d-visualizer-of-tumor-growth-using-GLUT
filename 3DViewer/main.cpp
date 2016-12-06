#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <vector>
#include "Cell.h"
#include "CellFactory.h"
#include "OGL.h"

#define SENS_ROT     5.0
#define SENS_OBS     2.0
#define SENS_TRANSL  30.0

//Globals
GLint	WINDOW_WIDTH = 500,
		WINDOW_HEIGHT = 500; //Simulation World + 2.0*Displacement

//Observer Position
Vector3 observer, obsini;

//Light Position
Vector3 light(320.0f, 228.0f, 500.0f);

//Mouse Movement
Vector3 rotation,
		rotIni,
		pos;

GLint bpress;

std::vector<Cell> cells;

void glutSetup(void);
void glutDisplay(void);
void glutProjection(void);
void glutMotion(int x, int y);
void glutKeyboard(unsigned char key, int x, int y);
void glutMouse(int button, int state, int x, int y);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	CellFactory factory("saida_anna.dat");
	cells = factory.fabricate();
	observer = obsini = Vector3((factory.min.x + factory.max.x) / 2, (factory.min.y + factory.max.y) / 2, 900);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("3D Viewer");
	glutSetup();
	glutDisplayFunc(glutDisplay);
	glutMouseFunc(glutMouse);
	glutMotionFunc(glutMotion);
	glutKeyboardFunc(glutKeyboard);
	glutMainLoop();

	return 0;
}

//Setup
void glutSetup(void) {
	//Background Color (White)
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//Z-Buffer & Light
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//Transparency & Model Light
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

	//Ignore Material Properties: PREDOMINANCE OF glColor3f DIRECTIVES
	glEnable(GL_COLOR_MATERIAL);

	////Light Color (RGBA) & Position
	GLfloat clight[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat plight[] = { light.x, light.y, light.z, 1.0 }; //Positional Light (1.0)

	//										//Light Parameters
	glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, clight);
	glLightfv(GL_LIGHT0, GL_POSITION, plight);

	glutProjection();
}

//Projection
void glutProjection(void) {
	//Projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 1.0, 2000.0);

	//ModelView
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(observer.x, observer.y, observer.z, (GLfloat)WINDOW_HEIGHT/2, (GLfloat)WINDOW_WIDTH/2, 0.0, 0.0, 1.0, 0.0); //EYE, CENTER & UP
}

//Display Function
void glutDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ogl::Render render;
	
	render.renderCells(cells);

	glutSwapBuffers();
}

//Keyboard Actions
void glutKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //ESC: EXIT
		exit(0);
	case 'x': //OBSERVER MOVEMENT -X
		observer.x -= 5;
		glutProjection();
		break;
	case 'X': //OBSERVER MOVEMENT +X
		observer.x += 5;
		glutProjection();
		break;
	case 'y': //OBSERVER MOVEMENT -Y
		observer.y -= 5;
		glutProjection();
		break;
	case 'Y': //OBSERVER MOVEMENT +Y
		observer.y += 5;
		glutProjection();
		break;
	case 'z': //OBSERVER MOVEMENT -Z
		observer.z -= 5;
		glutProjection();
		break;
	case 'Z': //OBSERVER MOVEMENT +Z
		observer.z += 5;
		glutProjection();
		break;
	}

	glutPostRedisplay();
}

//Mouse Action
void glutMouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		pos.x = x;
		pos.y = y;
		rotIni.x = rotation.x;
		rotIni.y = rotation.y;
		rotIni.z = rotation.z;
		bpress = button;
	}
	else
		bpress = -1;
}

//Mouse Motion
void glutMotion(int x, int y) {
	if (bpress == GLUT_LEFT_BUTTON) {
		rotation.y = rotIni.y - (pos.x - x) / SENS_ROT;
		rotation.x = rotIni.x - (pos.y - y) / SENS_ROT;
	}
	else if (bpress == GLUT_RIGHT_BUTTON) {
		int dz = pos.y - y;
		observer.z = observer.z + dz / SENS_OBS;
	}
	else if (bpress == GLUT_MIDDLE_BUTTON) {
		int dx = pos.x - x;
		int dy = pos.y - y;
		observer.x = observer.x + dx / SENS_TRANSL;
		observer.y = observer.y + dy / SENS_TRANSL;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslated(-observer.x, -observer.y, -observer.z);
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glutPostRedisplay();
}

