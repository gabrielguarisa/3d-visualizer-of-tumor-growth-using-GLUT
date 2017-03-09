#ifndef RENDER
#define RENDER

#include <GL/glut.h>
#include <vector>
#include "Cell.h"
#include "Util.h"

namespace ogl {
	#define NUM_SEGMENTS 20
	#define CELL_GAP 15

	class Render {
	private:
		Vector3	min_,		// Left and Top limits
				max_,		// Right and Bottom limits
				middle_;	// (min + max) / 2

		void drawCell_(Cell c, ViewMode viewMode, ColorRGBA primary, ColorRGBA secondary, ColorRGBA nut, ColorRGBA egf);
	public:

		Vector3 minimumLimit, // Left and Top limits
				maximumLimit; // Right and Bottom limits

		Render(Vector3 minimumLimit, Vector3 maximumLimit);

		void renderCells(std::vector<Cell> cells, ViewMode viewMode, CellDisplayTypes cellDT, std::vector<std::vector<std::vector<float> > >  nutGrid, std::vector<std::vector<std::vector<float> > >  egfGrid);

		void renderLines();

		Vector3 getMiddle();

		Vector3 getMin();

		Vector3 getMax();
	};
}

#endif /* end of include guard: RENDER */
