#pragma once

#include "Util.h"

/*
** CELL
*/
class Cell
{
public:
	CellType type;

	Vector3 coordinates,
			v;

	GLfloat	radius,
			calcification,
			nucleusRadius;

	Cell(CellType type, Vector3 coordinates, float radius, float calcification, float nucleusRadius, Vector3 v = Vector3(0.0f, 0.0f, 0.0f));

};
