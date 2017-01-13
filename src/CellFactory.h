#pragma once

#include <fstream>
#include <cmath>
#include <string>
#include "CellFrame.h"

/*
** CELL FACTORY
*/
class CellFactory
{
public:
    CellFrame* fabricate(std::string fileName);
};
