#ifndef RENDER
#define RENDER

#include <GL/glut.h>
#include <vector>
#include "Cell.h"

namespace ogl {
	#define NUM_SEGMENTS 20
	#define CELL_GAP 15

	class Render {
	private:
		Vector3	min_,		// Left and Top limits
				max_,		// Right and Bottom limits
				middle_;	// (min + max) / 2
	public:

		Vector3 minimumLimit, // Left and Top limits
				maximumLimit; // Right and Bottom limits

		Render(Vector3 minimumLimit, Vector3 maximumLimit);

		void renderCells(std::vector<Cell> cells, ViewMode viewMode, CellDisplayTypes cellDT);

		void renderLines();

		Vector3 getMiddle();

		Vector3 getMin();

		Vector3 getMax();
	};
}

#endif /* end of include guard: RENDER */
