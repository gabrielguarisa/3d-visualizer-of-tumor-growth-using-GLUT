#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <vector>
#include "Cell.h"
#include "CellFactory.h"

//OpenGL Parameters
#define NUM_SEGMENTS 100
#define SENS_ROT     5.0
#define SENS_OBS     2.0
#define SENS_TRANSL  30.0

//Globals
GLint	WINDOW_WIDTH = 500,
		WINDOW_HEIGHT = 500; //Simulation World + 2.0*Displacement

//Observer Position
Vector3 observer;

//Light Position
Vector3 light(320.0f, 228.0f, 500.0f);

//Mouse Movement
Vector3 rotation,
		rotIni,
		obsIni,
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
	observer = Vector3((factory.min.x + factory.max.x)/2, (factory.min.y + factory.max.y) / 2, 900);
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

	//Light Color (RGBA) & Position
	GLfloat clight[] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat plight[] = { light.x, light.y, light.z, 1.0 }; //Positional Light (1.0)

											//Light Parameters
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

	for (int i = 0; i < cells.size(); i++) {
		glPushMatrix();
		glTranslatef(cells[i].coordinates.x, cells[i].coordinates.y, cells[i].coordinates.z);//zpos
		switch (cells[i].type) {
		case NEC: //Necrotic Cell (0): RGB DEPENDS ON CALCIFICATION LEVEL
			glColor4f((cells[i].calcification)*1.0f, 0.0f, (1 - cells[i].calcification)*1.0f, 1.0f);
			glutSolidSphere(cells[i].radius, NUM_SEGMENTS, NUM_SEGMENTS);
			break;
		case QUI: //Quiescent Cell (1): RGB #CCCCFF & RGB #4D4DFF
			glColor4f(0.302f, 0.302f, 1.0f, 1.0f);
			glutSolidSphere(cells[i].nucleusRadius, NUM_SEGMENTS, NUM_SEGMENTS);
			glDepthMask(GL_FALSE);
			glColor4f(0.8f, 0.8f, 1.0f, 0.2f);
			glutSolidSphere(cells[i].radius, NUM_SEGMENTS, NUM_SEGMENTS);
			glDepthMask(GL_TRUE);
			break;
		case PRO: //Proliferative Cell (2): RGB #00CC00 & RGB #4D4DFF
			glColor4f(0.302f, 0.302f, 1.0f, 1.0f);
			glutSolidSphere(cells[i].nucleusRadius, NUM_SEGMENTS, NUM_SEGMENTS);
			glDepthMask(GL_FALSE);
			glColor4f(0.0f, 0.8f, 0.0f, 0.2f);
			glutSolidSphere(cells[i].radius, NUM_SEGMENTS, NUM_SEGMENTS);
			glDepthMask(GL_TRUE);
			break;
		case APO: //Apoptotic Cell (4): RGB #E60000 & RGB #4D4DFF
			glColor4f(0.302f, 0.302f, 1.0f, 1.0f);
			glutSolidSphere(cells[i].nucleusRadius, NUM_SEGMENTS, NUM_SEGMENTS);
			glDepthMask(GL_FALSE);
			glColor4f(0.902f, 0.0f, 0.0f, 0.2f);
			glutSolidSphere(cells[i].radius, NUM_SEGMENTS, NUM_SEGMENTS);
			glDepthMask(GL_TRUE);
			break;
		case G1: //G1 Cell (5): RGB #00CC00 & RGB #4D4DFF
			glColor4f(0.302f, 0.302f, 1.0f, 1.0f);
			glutSolidSphere(cells[i].nucleusRadius, NUM_SEGMENTS, NUM_SEGMENTS);
			glColor4f(0.0f, 0.8f, 0.0f, 0.2f);
			glDepthMask(GL_FALSE);
			glutSolidSphere(cells[i].radius, NUM_SEGMENTS, NUM_SEGMENTS);
			glDepthMask(GL_TRUE);
			break;
		case NOR: //Normal Cell (6): RGB #E8E8F5 & RGB #DDDDF7
			glColor4f(0.867f, 0.867f, 0.969f, 1.0f);
			glutSolidSphere(cells[i].nucleusRadius, NUM_SEGMENTS, NUM_SEGMENTS);
			glDepthMask(GL_FALSE);
			glColor4f(0.91f, 0.91f, 0.961f, 0.2f);
			glutSolidSphere(cells[i].radius, NUM_SEGMENTS, NUM_SEGMENTS);
			glDepthMask(GL_TRUE);
			break;
		default:
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			glutSolidSphere(cells[i].radius, NUM_SEGMENTS, NUM_SEGMENTS);
			break;

		}
		glPopMatrix();
	}

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
	case 'j': //LIGHT MOVEMENT -X
		light.x -= 5;
		glutProjection();
		break;
	case 'J': //LIGHT MOVEMENT +X
		light.x += 5;
		glutProjection();
		break;
	case 'k': //LIGHT MOVEMENT -Y
		light.y -= 5;
		glutProjection();
		break;
	case 'K': //LIGHT MOVEMENT +Y
		light.y += 5;
		glutProjection();
		break;
	case 'l': //LIGHT MOVEMENT -Z
		light.z -= 5;
		glutProjection();
		break;
	case 'L': //LIGHT MOVEMENT +Z
		light.z += 5;
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
		obsIni.x = observer.x;
		obsIni.y = observer.y;
		obsIni.z = observer.z;
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
		int dx = pos.x - x;
		int dy = pos.y - y;

		rotation.y = rotIni.y - dx / SENS_ROT;
		rotation.x = rotIni.x - dy / SENS_ROT;
	}
	else if (bpress == GLUT_RIGHT_BUTTON) {
		int dz = pos.y - y;
		observer.z = obsIni.z + dz / SENS_OBS;
	}
	else if (bpress == GLUT_MIDDLE_BUTTON) {
		int dx = pos.x - x;
		int dy = pos.y - y;
		observer.x = obsIni.x + dx / SENS_TRANSL;
		observer.y = obsIni.y - dy / SENS_TRANSL;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-observer.x, -observer.y, -observer.z);
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glutPostRedisplay();
}

