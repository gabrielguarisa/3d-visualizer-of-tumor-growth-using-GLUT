#pragma once

#include <vector>
#include "Cell.h"

//Observer Position
extern Vector3 observer, obsini;

//Light Position
extern Vector3 light;

//Mouse Movement
extern Vector3	rotation,
				rotIni,
				pos;

extern GLint bpress;

extern std::vector<Cell> cells;

extern GLint	windowWidth,
				windowHeight;