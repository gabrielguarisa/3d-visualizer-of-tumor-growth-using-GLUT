#pragma once

#include "Screenshot.h"
#include "Global.h"

namespace ogl {
	#define SENS_ROT    5.0
	#define SENS_OBS	2.0
	#define SENS_TRANSL	30.0
	#define SENS_SLICES	1

	#define ZOOM_MIN 100
	#define ZOOM_MAX 1800

	class GlutWindow {
	public:
		GlutWindow(int argc, char *argv[]);
		void glutSetup();
		static void glutDisplay();
		static void glutProjection();
		static void glutMotion(int x, int y);
		static void glutKeyboard(unsigned char key, int x, int y);
		static void glutMouse(int button, int state, int x, int y);
		void start();
	};

}