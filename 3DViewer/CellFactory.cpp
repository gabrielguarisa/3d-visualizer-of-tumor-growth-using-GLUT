#include "CellFactory.h"

CellFactory::CellFactory(std::string filename)
{
	time_ = xdomain_ = ydomain_ = zdomain_ = outcells_ = tumcells_ = 0.0;
	file_.open(filename);
	numCells = 0;
	file_ >> xdomain_ >> ydomain_;
	file_ >> numCells >> time_;
	file_ >> outcells_ >> tumcells_;

	cells_.reserve(numCells);
}

std::vector<Cell> CellFactory::fabricate()
{
	GLfloat	radius = 0.0,
			calcification = 0.0,
			nucleusRadius = 0.0;

	int type = 0;
	Vector3 pos, v;

	for (int i = 0; i < numCells; i++) {
		file_ >> type;
		file_ >> pos.x >> pos.y;
		file_ >> nucleusRadius >> radius >> calcification;
		file_ >> v.x >> v.y;

		Cell c((CellType)type, pos, radius, calcification, nucleusRadius, v);
		cells_.push_back(c);

		//all_.x += c.coordinates.x;
		//all_.y += c.coordinates.y;
		////all_.z += c.coordinates.z;

		//if (all_.z < c.coordinates.x)
		//	all_.z = c.coordinates.x;

		if (c.coordinates.x > max.x)
			max.x = c.coordinates.x;
		else if (c.coordinates.y < max.y)
			min.x = c.coordinates.x;

		if (c.coordinates.y > max.y)
			max.y = c.coordinates.y;
		else if (c.coordinates.y < max.y)
			min.y = c.coordinates.y;
	}
	return cells_;
}
