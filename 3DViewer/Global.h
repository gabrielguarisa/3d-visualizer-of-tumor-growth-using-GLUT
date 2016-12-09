#pragma once

#include <vector>
#include "Render.h"
#include "Cell.h"
#include "Screenshot.h"

//Observer Position
extern Vector3 observer;

//Light Position
extern Vector3 light;

//Mouse Movement
extern Vector3	rotation,
				rotIni,
				pos;

extern GLint bpress;

extern std::vector<Cell> cells;

extern std::vector<Cell> temp; //remove
extern bool trueRender; //remove

extern ogl::Render *render;

extern GLint	windowWidth,
				windowHeight;

extern GLboolean lines;

extern ogl::Screenshot screenshot;
