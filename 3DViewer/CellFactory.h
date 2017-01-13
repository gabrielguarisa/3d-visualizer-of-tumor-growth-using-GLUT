#pragma once

#include <fstream>

#include <cmath>
#include "CellFrame.h"
#include <string>

class CellFactory
{
public:
	CellFrame* fabricate(std::string fileName);
	//std::vector<CellFrame> fabricateVector(std::vector<std::string> files);
};
