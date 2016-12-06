#include "Cell.h"

Cell::Cell(CellType type, Vector3 coordinates, float radius, float calcification, float nucleusRadius, Vector3 v)
{
	this->type = type;
	this->coordinates = coordinates;
	this->radius = radius;
	this->calcification = calcification;
	this->nucleusRadius = nucleusRadius;
	this->v = v;
}