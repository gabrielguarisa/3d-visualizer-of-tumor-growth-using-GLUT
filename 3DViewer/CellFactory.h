#pragma once
#include <fstream>
#include <vector>

#include "Cell.h"

class CellFactory
{
private:
	std::ifstream file_;
	std::vector<Cell> cells_;

	/*
	* ?
	*/
	float	time_,
			xdomain_,
			ydomain_,
			zdomain_;

	float	outcells_,
			tumcells_;
	/*
	*
	*/

public:
	int numCells;

	Vector3 min, max;

	CellFactory(std::string filename);

	std::vector<Cell> fabricate();

};