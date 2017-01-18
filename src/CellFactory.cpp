#include "CellFactory.h"

CellFrame* CellFactory::fabricate(std::string fileName)
{
	// FILE
	std::ifstream file;
	//

	// CellFrame stuff
	GLfloat	outCells = 0.0,
			tumCells = 0.0,
			time = 0.0;

	GLint numCells = 0;

	Vector3	domain,
			min,
			max;

	std::vector<Cell> cells;
	//

	// Cell stuff
	GLfloat radius = 0.0,
			calcification = 0.0,
			nucleusRadius = 0.0;

	GLint 	type = 0;

	Vector3 pos,
			v;
	//

	file.open(fileName.c_str());

	file >> domain.x >> domain.y >> domain.z;
	file >> numCells >> time;
	file >> outCells >> tumCells;

	// Reading all cells
	for (int i = 0; i < numCells; i++) {
		file >> type;
		file >> pos.x >> pos.y >> pos.z ;
		file >> nucleusRadius >> radius >> calcification;
		file >> v.x >> v.y >> v.z;

		Cell c((CellType)type, pos, radius, calcification, nucleusRadius, v);
		cells.push_back(c);

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
	//
	file.close();
	return new CellFrame(time, domain, outCells, tumCells, numCells, cells, min, max);
}
