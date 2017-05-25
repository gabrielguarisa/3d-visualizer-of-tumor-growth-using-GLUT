#ifndef RENDER
#define RENDER

#include <GL/glut.h>
#include <vector>
#include <array>
#include "Cell.h"
#include "Util.h"
#include "ConfigHandler.h"

namespace ogl {
	#define NUM_SEGMENTS 20

	class Render {
	private:
		void drawCell_(Cell c, ViewMode viewMode, ColorRGBA primary, ColorRGBA secondary, double nutValue, double egfValue);
	public:

		void renderCells(std::vector<Cell> cells, std::vector<std::vector<std::vector<float> > >  nutGrid, std::vector<std::vector<std::vector<float> > >  egfGrid, ConfigHandler* config);

		void renderLines(ConfigHandler* config);

		void axisDraw();

		void generateColor(ColorRGBA *c, double value, double min = 0.0, double max = 0.6);
	};
}

#endif /* end of include guard: RENDER */
