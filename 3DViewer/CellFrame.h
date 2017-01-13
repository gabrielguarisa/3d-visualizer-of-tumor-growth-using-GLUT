#ifndef CELLSFRAME_H
#define CELLSFRAME_H

#include <vector>
#include "Cell.h"

class CellFrame
{
private:
    float	time_;

    Vector3 domain_;

    float	outCells_,
            tumCells_;

    int numCells_;

    Vector3 min_, max_;

public:
    CellFrame(float time, Vector3 domain, float outCells, float tumCells, int numCells, std::vector<Cell> cells, Vector3 min, Vector3 max);

    std::vector<Cell> cells;

    Vector3 getMin();

    Vector3 getMax();
};

#endif /* end of include guard: CELLSFRAME_H */
