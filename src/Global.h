#ifndef GLOBAL
#define GLOBAL

#include <vector>
#include "Render.h"
#include "Frame.h"
#include "Screenshot.h"
#include "ConfigHandler.h"

extern ConfigHandler* config;

extern std::vector<Frame*> frames;

extern ogl::Render *render;

#endif /* end of include guard: GLOBAL */
