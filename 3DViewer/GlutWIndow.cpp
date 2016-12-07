#include "GlutWindow.h"

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
	glutSpecialFunc(this->glutSpecial);
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

	render->renderCells(cells);

	if(lines)
		render->renderLines();

	glutSwapBuffers();
}

//Keyboard Actions
void ogl::GlutWindow::glutKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //ESC: EXIT
		exit(0);
	case 'a': 
		render->minimumLimit.x -= SENS_SLICES;
		break;
	case 'A':
		render->minimumLimit.x += SENS_SLICES;
		break;
	case 'd':
		render->maximumLimit.x += SENS_SLICES;
		break;
	case 'D':
		render->maximumLimit.x -= SENS_SLICES;
		break;
	case 's':
		render->minimumLimit.y -= SENS_SLICES;
		break;
	case 'S':
		render->minimumLimit.y += SENS_SLICES;
		break;
	case 'w':
		render->maximumLimit.y += SENS_SLICES;
		break;
	case 'W':
		render->maximumLimit.y -= SENS_SLICES;
		break;
	case 'l': case 'L':
		lines = !lines;
		break;
	case '0':
		render->maximumLimit = render->getMax();
		render->minimumLimit = render->getMin();
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
		if (observer.z + dz / SENS_OBS > ZOOM_MIN && observer.z + dz / SENS_OBS < ZOOM_MAX)
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