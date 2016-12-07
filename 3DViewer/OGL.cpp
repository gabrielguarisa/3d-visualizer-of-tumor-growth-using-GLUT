#include "OGL.h"

void ogl::Render::renderCells(std::vector<Cell> cells)
{
	for (int i = 0; i < cells.size(); i++) {
		glPushMatrix();
		glTranslatef(cells[i].coordinates.x, cells[i].coordinates.y, cells[i].coordinates.z);
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
			glutSolidSphere(cells[i].nucleusRadius, NUM_SEGMENTS, NUM_SEGMENTS);
			break;

		}
		glPopMatrix();
	}
}

ogl::GlutWindow::GlutWindow(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - windowWidth) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - windowHeight) / 2);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("3D Viewer");

	this->glutSetup();

	glutDisplayFunc(this->glutDisplay);
	glutMouseFunc(this->glutMouse);
	glutMotionFunc(this->glutMotion);
	glutKeyboardFunc(this->glutKeyboard);
}


void ogl::GlutWindow::glutSetup() {
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

	this->glutProjection();
}

//Projection
void ogl::GlutWindow::glutProjection() {
	//Projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)windowWidth / (GLfloat)windowHeight, 1.0, 2000.0);

	//ModelView
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(observer.x, observer.y, observer.z, (GLfloat)windowWidth / 2, (GLfloat)windowHeight / 2, 0.0, 0.0, 1.0, 0.0); //EYE, CENTER & UP
}

//Display Function
void ogl::GlutWindow::glutDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ogl::Render render;
	render.renderCells(cells);

	glutSwapBuffers();
}

//Keyboard Actions
void ogl::GlutWindow::glutKeyboard(unsigned char key, int x, int y) {
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
void ogl::GlutWindow::glutMouse(int button, int state, int x, int y) {
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
void ogl::GlutWindow::glutMotion(int x, int y) {
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

void ogl::GlutWindow::start() 
{
	glutMainLoop();
}