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

		if (c.coordinates.x > max.x)
			max.x = c.coordinates.x;
		else if (c.coordinates.y < min.y)
			min.x = c.coordinates.x;

		if (c.coordinates.y > max.y)
			max.y = c.coordinates.y;
		else if (c.coordinates.y < min.y)
			min.y = c.coordinates.y;

		if (c.coordinates.z > max.z)
			max.z = c.coordinates.z;
		else if (c.coordinates.z < min.z)
			min.z = c.coordinates.z;

	}
	return cells_;
}

std::vector<Cell> CellFactory::simulate3D()//remove
{
	int r = 250;
	std::vector<Cell> tempCells;
	for (int i = 0; i < this->cells_.size(); i++)
	{
		Vector3 pos = cells_[i].coordinates;
		for (int j = -r; j < r; j += 13)
		{
			pos.z = j;
			if (((pow(cells_[i].coordinates.x - 249.167, 2)) + (pow(cells_[i].coordinates.y - 249.723, 2)) + (pow(pos.z, 2)) <= pow(r, 2)))
			{
				tempCells.push_back(Cell(cells_[i].type, pos, cells_[i].radius, cells_[i].calcification, cells_[i].nucleusRadius, cells_[i].v));
			}
		}
	}
	return tempCells;
}
