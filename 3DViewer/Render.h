#pragma once

#include <GL/glut.h>
#include <vector>
#include "Cell.h"

namespace ogl {
	#define NUM_SEGMENTS 25

	class Render {
	private:
		GLfloat	middleX_,
			middleY_;
	public:

		GLfloat rightLimit,
			leftLimit,
			topLimit,
			bottomLimit;

		Render(GLfloat rightLimit, GLfloat leftLimit, GLfloat topLimit, GLfloat bottomLimit);
		void renderCells(std::vector<Cell> cells);

		GLfloat getMiddleX();

		GLfloat getMiddleY();
	};
}