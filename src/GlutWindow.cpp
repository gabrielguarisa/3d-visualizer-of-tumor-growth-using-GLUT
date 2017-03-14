#include "GlutWindow.h"

//Observer Position
Vector3 observer;

//Mouse Movement
Vector3	rotation,
		rotIni,
		pos;

GLint bpress;

ogl::GlutWindow::GlutWindow(int argc, char * argv[])
{
	glutInit(&argc, argv);
	observer = Vector3(frames[0]->domain.x, frames[0]->domain.y, frames[0]->domain.z + 600.0f);
	//glutInitWindowposition((glutGet(GLUT_SCREEN_WIDTH) - config->window.width) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - config->window.height) / 2);
	glutInitWindowSize(config->window.width, config->window.height);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow(config->window.title.c_str());
	glutReshapeWindow(config->window.width, config->window.height);

	if(config->window.fullscreen)
		glutFullScreen();

	this->glutSetup();

	glutReshapeFunc(this->glutReshape);
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

	this->glutProjection();
}

//Projection
void ogl::GlutWindow::glutProjection() {
	//Projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)config->window.width / (GLfloat)config->window.height, 1.0, 2000.0);

	//ModelView
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(observer.x/2, observer.y/2, observer.z/1.2, observer.x/2, observer.y/2, observer.x/2, 0.0, 1.0, 0.0); //EYE, CENTER & UP
}

//Keyboard Actions
void ogl::GlutWindow::glutKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: //ESC: EXIT
		exit(0);
	case 'p': // PrintScreen PNG
		screenshot.screenshot(PNG);
		break;
	case 'P': // PrintScreen JPG
		screenshot.screenshot(JPG);
		break;
	case 'o':
		screenshot.startLongScreenshot();
		break;
	case 'O':
		screenshot.stopLongScreenshot();
		break;
				/*** SLICES CONTROL ***/
				/*** lowercase -> out ***/
				/*** UPPERCASE -> center ***/
	case 'a':
		config->display.lines.minimumLimit.x -= SENS_SLICES;
		break;
	case 'A':
		config->display.lines.minimumLimit.x += SENS_SLICES;
		break;
	case 'd':
		config->display.lines.maximumLimit.x += SENS_SLICES;
		break;
	case 'D':
		config->display.lines.maximumLimit.x -= SENS_SLICES;
		break;
	case 's':
		config->display.lines.minimumLimit.y -= SENS_SLICES;
		break;
	case 'S':
		config->display.lines.minimumLimit.y += SENS_SLICES;
		break;
	case 'w':
		config->display.lines.maximumLimit.y += SENS_SLICES;
		break;
	case 'W':
		config->display.lines.maximumLimit.y -= SENS_SLICES;
		break;
	case 'q':
		config->display.lines.maximumLimit.z += SENS_SLICES;
		break;
	case 'Q':
		config->display.lines.maximumLimit.z -= SENS_SLICES;
		break;
	case 'e':
		config->display.lines.minimumLimit.z -= SENS_SLICES;
		break;
	case 'E':
		config->display.lines.minimumLimit.z += SENS_SLICES;
		break;
	case 'l': case 'L': // Show/Hide Lines
		config->display.showLines = !config->display.showLines;
		break;
	case 'i': case 'I': // Show/Hide Info
		config->display.showInfo = !config->display.showInfo;
		break;
	case '0':	// reset Slices
		config->display.lines.maximumLimit = frames[0]->domain;
		config->display.lines.minimumLimit = Vector3();
		break;


	/*** CELL VISIBILITY ***/
	case '1':
		config->display.cells.NEC.visibility = !config->display.cells.NEC.visibility;
		break;
	case '2':
		config->display.cells.QUI.visibility = !config->display.cells.QUI.visibility;
		break;
	case '3':
		config->display.cells.PRO.visibility = !config->display.cells.PRO.visibility;
		break;
	case '4':
		config->display.cells.HIP.visibility = !config->display.cells.HIP.visibility;
		break;
	case '5':
		config->display.cells.APO.visibility = !config->display.cells.APO.visibility;
		break;
	case '6':
		config->display.cells.G1.visibility = !config->display.cells.G1.visibility;
		break;
	case '7':
		config->display.cells.NOR.visibility = !config->display.cells.NOR.visibility;
		break;

	/*** CHANGE CELL ***/
	case ',':
		if(config->player.state != PAUSE)
			config->player.state = PAUSE;
		else
			config->player.state = PREVIOUS;
		break;
	case '.':
		if(config->player.state != PAUSE)
			config->player.state = PAUSE;
		else
			config->player.state = NEXT;
		break;
	case '<':
		if(config->player.state == REVERSE)
			config->player.state = PAUSE;
		else
			config->player.state = REVERSE;
		break;
	case '>':
		if(config->player.state == PLAY)
			config->player.state = PAUSE;
		else
			config->player.state = PLAY;
		break;
	case 'n':
		config->player.frame = 0;
		break;
	case 'N':
		config->player.frame = frames.size() - 1;
		break;

	case 'z':
		config->display.viewMode = STD;
		break;
	case 'x':
		config->display.viewMode = NUT;
		break;
	case 'c':
		config->display.viewMode = EGF;
		break;
	case 'f': case 'F':
		if(config->window.fullscreen)
		{
			glutReshapeWindow(config->window.width, config->window.height);
			config->window.fullscreen = false;
		}else
		{
			glutFullScreen();
			config->window.fullscreen = true;
		}
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
	glTranslated(-observer.x/2, -observer.y/2, -observer.z/1.2);
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);

	glutPostRedisplay();
}

void ogl::GlutWindow::start() {
	glutMainLoop();
}

void ogl::GlutWindow::renderString(GLdouble x, GLdouble y, std::string text) {
	glMatrixMode( GL_PROJECTION );
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D( 0, 1280, 0, 1024 );

	glMatrixMode( GL_MODELVIEW );
	glPushMatrix();
	glLoadIdentity();
		glColor3f(0.0f, 0.0f, 0.0f);
		glRasterPos2d(x, y);

		for (int i = 0; i < text.length(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
		}
		glPopMatrix();

	glMatrixMode( GL_PROJECTION );
	glPopMatrix();
	glMatrixMode( GL_MODELVIEW );
}

//Display Function
void ogl::GlutWindow::glutDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	render->renderCells(frames[config->player.frame]->cells, config->display.viewMode, config->display.cells, config, nutGrids[config->player.frame], egfGrids[config->player.frame]);

	if(config->display.showInfo)
	{
		std::string info = 	"agents: " +  std::to_string(frames[config->player.frame]->cells.size()) + "    out cells: " +  std::to_string(frames[config->player.frame]->outCells)  + "    tumor cells: " +  std::to_string(frames[config->player.frame]->tumorCells)  + "    time stamp: " +  std::to_string(frames[config->player.frame]->time);
		GlutWindow::renderString(10, 990, info);
	}

	if(config->display.showLines)
		render->renderLines(config);

	screenshot.longScreenshotWatch();

	GlutWindow::play();

	glutSwapBuffers();
}

void ogl::GlutWindow::glutReshape(GLsizei width, GLsizei height) {
	if (height == 0) height = 1;                // To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
	glLoadIdentity();             // Reset
	// Enable perspective projection with fovy, aspect, zNear and zFar
		gluPerspective(45.0, (GLfloat)aspect, 1.0, 2000.0);
}

void ogl::GlutWindow::play() {
	if(config->player.state != PAUSE)
	{
		switch (config->player.state) {
			case PLAY:
				if(config->player.frame < frames.size()-1)
					config->player.frame++;
				else
					config->player.state = PAUSE;
				break;
			case REVERSE:
				if(config->player.frame > 0)
					config->player.frame--;
				else
					config->player.state = PAUSE;
				break;
			case PREVIOUS:
				if(config->player.frame > 0)
					config->player.frame--;
				config->player.state = PAUSE;
				break;
			case NEXT:
				if(config->player.frame < frames.size() - 1)
					config->player.frame++;
				config->player.state = PAUSE;
				break;
			default:
				config->player.state = PAUSE;
				break;
		}
		glutPostRedisplay();
	}
}
