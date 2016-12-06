#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

//OpenGL Parameters
#define NUM_SEGMENTS 100
#define SENS_ROT     5.0
#define SENS_OBS     20.0
#define SENS_TRANSL  30.0

//Globals
int WINDOW_WIDTH = 500; //Simulation World + 2.0*Displacement
int WINDOW_HEIGHT = 500; //Simulation World + 2.0*Displacement

						 //Show Axis
int axis_bool = 1;

//Observer Position
float obsx = 0.0;
float obsy = 0.0;
float obsz = 500.0;

//Light Position
float lx = 320.0;
float ly = 228.0;
float lz = 500.0;

//Mouse Movement
float rotx = 0.0;
float roty = 0.0;
float rotz = 0.0;
float rotx_ini, roty_ini, rotz_ini;
float obsx_ini, obsy_ini, obsz_ini;
int bpress, x_ini, y_ini, z_ini;

//Cell Types
#define NEC 0 //Necrotic Cell
#define QUI 1 //Quiescent Cell
#define PRO 2 //Proliferative Cell
#define HIP 3 //Hipoxic Cell
#define APO 4 //Apoptotic Cell
#define G1  5 //Cell G1 State
#define NOR 6 //Normal Cell

void axisDraw(void);
void glutSetup(void);
void glutDisplay(void);
void glutProjection(void);
void glutMotion(int x, int y);
void glutSpecial(int key, int x, int y);
void glutReshape(int width, int height);
void glutKeyboard(unsigned char key, int x, int y);
void glutMouse(int button, int state, int x, int y);

//Cells' File
void readFile(char* filename);

//Cells' Globals
int *ctype;
float cells = 0;
float *xpos, *ypos, *cellrn, *cellr, *calc;

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - WINDOW_WIDTH) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - WINDOW_HEIGHT) / 2);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("3D Viewer");
	glutSetup();
	readFile("saida_anna.dat");
	glutDisplayFunc(glutDisplay);
	glutReshapeFunc(glutReshape);
	glutMouseFunc(glutMouse);
	glutMotionFunc(glutMotion);
	glutKeyboardFunc(glutKeyboard);
	glutSpecialFunc(glutSpecial);
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
	GLfloat plight[] = { lx, ly, lz, 1.0 }; //Positional Light (1.0)

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
	gluPerspective(45.0, (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 1.0, 1000.0);

	//ModelView
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsx, obsy, obsz, 320.0, 228.0, 0.0, 0.0, 1.0, 0.0); //EYE, CENTER & UP
}

//Display Function
void glutDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (axis_bool)
		axisDraw();

	for (int i = 0; i < cells; i++) {
		glPushMatrix();
		glTranslatef(xpos[i], ypos[i], 0.0);//zpos
		switch (ctype[i]) {
		case NEC: //Necrotic Cell (0): RGB DEPENDS ON CALCIFICATION LEVEL
			glColor4f((calc[i])*1.0f, 0.0f, (1 - calc[i])*1.0f, 1.0f);
			glutSolidSphere(cellr[i], NUM_SEGMENTS, NUM_SEGMENTS);
			break;
		case QUI: //Quiescent Cell (1): RGB #CCCCFF & RGB #4D4DFF
			glColor4f(0.302f, 0.302f, 1.0f, 1.0f);
			glutSolidSphere(cellrn[i], NUM_SEGMENTS, NUM_SEGMENTS);
			glDepthMask(GL_FALSE);
			glColor4f(0.8f, 0.8f, 1.0f, 0.2f);
			glutSolidSphere(cellr[i], NUM_SEGMENTS, NUM_SEGMENTS);
			glDepthMask(GL_TRUE);
			break;
		case PRO: //Proliferative Cell (2): RGB #00CC00 & RGB #4D4DFF
			glColor4f(0.302f, 0.302f, 1.0f, 1.0f);
			glutSolidSphere(cellrn[i], NUM_SEGMENTS, NUM_SEGMENTS);
			glDepthMask(GL_FALSE);
			glColor4f(0.0f, 0.8f, 0.0f, 0.2f);
			glutSolidSphere(cellr[i], NUM_SEGMENTS, NUM_SEGMENTS);
			glDepthMask(GL_TRUE);
			break;
		case APO: //Apoptotic Cell (4): RGB #E60000 & RGB #4D4DFF
			glColor4f(0.302f, 0.302f, 1.0f, 1.0f);
			glutSolidSphere(cellrn[i], NUM_SEGMENTS, NUM_SEGMENTS);
			glDepthMask(GL_FALSE);
			glColor4f(0.902f, 0.0f, 0.0f, 0.2f);
			glutSolidSphere(cellr[i], NUM_SEGMENTS, NUM_SEGMENTS);
			glDepthMask(GL_TRUE);
			break;
		case G1: //G1 Cell (5): RGB #00CC00 & RGB #4D4DFF
			glColor4f(0.302f, 0.302f, 1.0f, 1.0f);
			glutSolidSphere(cellrn[i], NUM_SEGMENTS, NUM_SEGMENTS);
			glColor4f(0.0f, 0.8f, 0.0f, 0.2f);
			glDepthMask(GL_FALSE);
			glutSolidSphere(cellr[i], NUM_SEGMENTS, NUM_SEGMENTS);
			glDepthMask(GL_TRUE);
			break;
		case NOR: //Normal Cell (6): RGB #E8E8F5 & RGB #DDDDF7
			glColor4f(0.867f, 0.867f, 0.969f, 1.0f);
			glutSolidSphere(cellrn[i], NUM_SEGMENTS, NUM_SEGMENTS);
			glDepthMask(GL_FALSE);
			glColor4f(0.91f, 0.91f, 0.961f, 0.2f);
			glutSolidSphere(cellr[i], NUM_SEGMENTS, NUM_SEGMENTS);
			glDepthMask(GL_TRUE);
			break;
		default:
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
			glutSolidSphere(cellrn[i], NUM_SEGMENTS, NUM_SEGMENTS);
			break;

		}
		glPopMatrix();
	}

	glutSwapBuffers();
}

//Cells' File
void readFile(char* filename) {
	float time, xdomain, ydomain, zdomain;
	float outcells, tumcells;
	float zpos, vx, vy, vz;

	FILE* inpfile = fopen(filename, "r");

	//Input File: Specific Fields
	fscanf(inpfile, "%f\t%f\n", &xdomain, &ydomain);
	fscanf(inpfile, "%f\t%f\n", &cells, &time);
	fscanf(inpfile, "%f\t%f\n", &outcells, &tumcells);

	ctype = (int*)malloc(cells * sizeof(int));
	xpos = (float*)malloc(cells * sizeof(float));
	ypos = (float*)malloc(cells * sizeof(float));

	cellrn = (float*)malloc(cells * sizeof(float));
	cellr = (float*)malloc(cells * sizeof(float));
	calc = (float*)malloc(cells * sizeof(float));

	zdomain = 0.0;
	zpos = 0.0;
	vz = 0.0;

	float medx = 0.0;
	float medy = 0.0;
	float medz = 0.0;

	for (int i = 0; i < cells; i++) {
		fscanf(inpfile, "%d\n", &ctype[i]);
		fscanf(inpfile, "%f\t%f\n", &xpos[i], &ypos[i]);
		fscanf(inpfile, "%f\t%f\t%f\n", &cellrn[i], &cellr[i], &calc[i]);
		fscanf(inpfile, "%f\t%f\n", &vx, &vy);

		medx += xpos[i];
		medy += ypos[i];
		medz += zpos;

		if (medz < xpos[i])
			medz = xpos[i];
	}

	medx = medx / (float)cells;
	medy = medy / (float)cells;

	obsx = medx + 100;
	obsy = medy;
	obsz = medz + 300;

	glutProjection();
	fclose(inpfile);
}

//Draw Axis
void axisDraw(void) {
	glDisable(GL_LIGHTING);
	glLineWidth(3.0);

	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(50.0, 0.0, 0.0);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 50.0, 0.0);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 50.0);
	glEnd();

	glEnable(GL_LIGHTING);
	glLineWidth(1.0);
}

//Reshape
void glutReshape(int width, int height) {
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

//Keyboard Actions
void glutKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //ESC: EXIT
		exit(0);
	case 'a':
	case 'A': //SHOW & HIDE AXIS
		axis_bool = !axis_bool;
		break;
	case 'x': //OBSERVER MOVEMENT -X
		obsx -= 5;
		glutProjection();
		break;
	case 'X': //OBSERVER MOVEMENT +X
		obsx += 5;
		glutProjection();
		break;
	case 'y': //OBSERVER MOVEMENT -Y
		obsy -= 5;
		glutProjection();
		break;
	case 'Y': //OBSERVER MOVEMENT +Y
		obsy += 5;
		glutProjection();
		break;
	case 'z': //OBSERVER MOVEMENT -Z
		obsz -= 5;
		glutProjection();
		break;
	case 'Z': //OBSERVER MOVEMENT +Z
		obsz += 5;
		glutProjection();
		break;
	case 'j': //LIGHT MOVEMENT -X
		lx -= 5;
		glutProjection();
		break;
	case 'J': //LIGHT MOVEMENT +X
		lx += 5;
		glutProjection();
		break;
	case 'k': //LIGHT MOVEMENT -Y
		ly -= 5;
		glutProjection();
		break;
	case 'K': //LIGHT MOVEMENT +Y
		ly += 5;
		glutProjection();
		break;
	case 'l': //LIGHT MOVEMENT -Z
		lz -= 5;
		glutProjection();
		break;
	case 'L': //LIGHT MOVEMENT +Z
		lz += 5;
		glutProjection();
		break;
	}

	glutPostRedisplay();
}

//Glut Special Keys
void glutSpecial(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_HOME:
		obsx = 0.0;
		obsy = 0.0;
		obsz = 200.0;

		lx = 50.0;
		ly = 50.0;
		lz = 50.0;
		glutProjection();
		break;
	}

	glutPostRedisplay();
}

//Mouse Action
void glutMouse(int button, int state, int x, int y) {
	if (state == GLUT_DOWN) {
		x_ini = x;
		y_ini = y;
		obsx_ini = obsx;
		obsy_ini = obsy;
		obsz_ini = obsz;
		rotx_ini = rotx;
		roty_ini = roty;
		rotz_ini = rotz;
		bpress = button;
	}
	else
		bpress = -1;
}

//Mouse Motion
void glutMotion(int x, int y) {
	if (bpress == GLUT_LEFT_BUTTON) {
		int dx = x_ini - x;
		int dy = y_ini - y;

		roty = roty_ini - dx / SENS_ROT;
		rotx = rotx_ini - dy / SENS_ROT;
	}
	else if (bpress == GLUT_RIGHT_BUTTON) {
		int dz = y_ini - y;
		obsz = obsz_ini + dz / SENS_OBS;
	}
	else if (bpress == GLUT_MIDDLE_BUTTON) {
		int dx = x_ini - x;
		int dy = y_ini - y;
		obsx = obsx_ini + dx / SENS_TRANSL;
		obsy = obsy_ini - dy / SENS_TRANSL;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-obsx, -obsy, -obsz);
	glRotatef(rotx, 1, 0, 0);
	glRotatef(roty, 0, 1, 0);
	glutPostRedisplay();
}

