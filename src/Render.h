#ifndef RENDER
#define RENDER

#include <GL/glut.h>
#include <vector>
#include "Cell.h"
#include "Util.h"
#include "ConfigHandler.h"

namespace ogl {
	#define NUM_SEGMENTS 20

	class Render {
	private:
		void drawCell_(Cell c, ViewMode viewMode, ColorRGBA primary, ColorRGBA secondary, ColorRGBA nut, ColorRGBA egf);
	public:

		void renderCells(std::vector<Cell> cells, ViewMode viewMode, CellDisplayTypes cellDT, ConfigHandler* config, std::vector<std::vector<std::vector<float> > >  nutGrid, std::vector<std::vector<std::vector<float> > >  egfGrid);

		void renderLines(ConfigHandler* config);
	};
}

#endif /* end of include guard: RENDER */
