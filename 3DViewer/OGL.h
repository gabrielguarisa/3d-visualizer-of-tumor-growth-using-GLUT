#pragma once

#include <vector>
#include "Cell.h"

namespace ogl {
#define NUM_SEGMENTS 25

	class Render {
	private:
	
	public:
		void renderCells(std::vector<Cell> cells);
	};


}