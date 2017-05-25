#ifndef GLOBAL
#define GLOBAL

#include <vector>
#include "Render.h"
#include "CellFrame.h"
#include "Screenshot.h"
#include "ConfigHandler.h"

extern ConfigHandler* config;

extern Grid     nutGrids,
                egfGrids;

extern std::vector<CellFrame*> frames;

extern ogl::Render *render;

#endif /* end of include guard: GLOBAL */
