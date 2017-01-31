#ifndef CELL_FRAME
#define CELL_FRAME

#include <vector>
#include "Cell.h"

class CellFrame
{
public:
    int time, tumorCells, outCells;
    Vector3 domain;
    std::vector<Cell> cells;

    CellFrame(Vector3 domain = Vector3(), int time = 0, int outCells = 0, int tumorCells = 0, std::vector<Cell> cells = std::vector<Cell>())
    :
        domain(domain),
        time(time),
        outCells(outCells),
        tumorCells(tumorCells),
        cells(cells)
    {}

};

#endif /* end of include guard: CELL_FRAME */
