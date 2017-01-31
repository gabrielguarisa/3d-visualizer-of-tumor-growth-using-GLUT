#include "CellFrame.h"

CellFrame::CellFrame(float time, Vector3 domain, float outCells, float tumCells, int numCells, std::vector<Cell> cells)
{
    this->time_ = time;
    this->domain_ = domain;
    this->outCells_ = outCells;
    this->tumCells_ = tumCells;
    this->numCells_ = numCells;
    this->cells = cells;
}

Vector3 CellFrame::getDomain()
{
    return domain_;
}
