#pragma once

#include <vector>
#include "Render.h"
#include "CellFrame.h"
#include "Screenshot.h"
#include "ConfigFileHandler.h"

extern ConfigFileHandler* config;

//Observer Position
extern Vector3 observer;

//Light Position
extern Vector3 light;

//Mouse Movement
extern Vector3	rotation,
				rotIni,
				pos;

extern GLint bpress;

extern std::vector<std::vector<std::vector<std::vector<float> > > > nutGrids;
extern std::vector<std::vector<std::vector<std::vector<float> > > > egfGrids;
extern std::vector<CellFrame*> frames;
extern int 	frameNum,
			automaticPlay;

extern ogl::Render *render;

extern GLint	windowWidth,
				windowHeight;

extern GLboolean 	lines,
					showInfo;

extern ogl::Screenshot screenshot;

extern bool visibilityNEC,  /***  Necrotic Cell  ***/
			visibilityQUI,  /***  Quiescent Cell  ***/
			visibilityPRO,  /***  Proliferative Cell  ***/
			visibilityHIP,  /***  Hipoxic Cell  ***/
			visibilityAPO,  /***  Apoptotic Cell  ***/
			visibilityG1,   /***  Cell G1 State  ***/
			visibilityNOR;  /***  Normal Cell  ***/



// Camera position
extern float x, y; // initially 5 units south of origin
extern float deltaMove; // initially camera doesn't move

// Camera direction
extern float lx, ly; // camera points initially along y-axis
extern float angle; // angle of rotation for the camera direction
extern float deltaAngle; // additional angle change when dragging

// Mouse drag control
extern int isDragging; // true when dragging
extern int xDragStart; // records the x-coordinate when dragging starts

extern ViewMode viewMode;
