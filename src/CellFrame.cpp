#include "CellFrame.h"

CellFrame::CellFrame(float time, Vector3 domain, float outCells, float tumCells, int numCells, std::vector<Cell> cells, Vector3 min, Vector3 max)
{
    this->time_ = time;
    this->domain_ = domain;
    this->outCells_ = outCells;
    this->tumCells_ = tumCells;
    this->numCells_ = numCells;
    this->cells = cells;
    this->min_ = min;
    this->max_ = max;
}

Vector3 CellFrame::getMin()
{
    return min_;
}

Vector3 CellFrame::getMax()
{
    return max_;
}
