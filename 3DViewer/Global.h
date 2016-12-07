#pragma once

#include <vector>
#include "Render.h"
#include "Cell.h"

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

extern ogl::Render *render;

extern GLint	windowWidth,
				windowHeight;
