#include "Render.h"
#include <cmath>
#include <iostream>

float accuracy = 10.0f;

void ogl::Render::drawCell_(Cell c, ViewMode viewMode, ColorRGBA primary, ColorRGBA secondary, ColorRGBA nut, ColorRGBA egf) {
	glPushMatrix();

	glTranslatef(c.coordinates.x, c.coordinates.y, c.coordinates.z);

	if(viewMode == STD)
	{
		if (c.type == NEC)
			glColor4f((c.calcification)*primary.r, primary.g, (1 - c.calcification)*primary.b, primary.a);
		else
			glColor4f(primary.r, primary.g, primary.b, primary.a);
	}
	else if(viewMode == NUT)
		glColor4f(nut.r, nut.g, nut.b, nut.a);
	else if(viewMode == EGF)
		glColor4f(egf.r, egf.g, egf.b, egf.a);

	glutSolidSphere(c.nucleusRadius, NUM_SEGMENTS, NUM_SEGMENTS);

	if (c.type != NEC)
	{
		glDepthMask(GL_FALSE);
		if(viewMode == STD)
			glColor4f(secondary.r, secondary.g, secondary.b, secondary.a);
		else if(viewMode == NUT)
			glColor4f(nut.r, nut.g, nut.b, nut.a - 0.8);
		else if(viewMode == EGF)
			glColor4f(egf.r, egf.g, egf.b, egf.a - 0.8);
		glutSolidSphere(c.radius, NUM_SEGMENTS, NUM_SEGMENTS);
		glDepthMask(GL_TRUE);
	}

	glPopMatrix();
}

ogl::Render::Render(Vector3 minimumLimit, Vector3 maximumLimit)
{
	this->minimumLimit = this->min_ = minimumLimit - CELL_GAP;
	this->maximumLimit = this->max_ = maximumLimit + CELL_GAP;
	this->middle_ = Vector3((min_.x + max_.x) / 2, (min_.y + max_.y) / 2, (min_.z + max_.z) / 2);
}

void ogl::Render::renderCells(std::vector<Cell> cells, ViewMode viewMode, CellDisplayTypes cellDT, std::vector<std::vector<std::vector<float> > >  nutGrid, std::vector<std::vector<std::vector<float> > >  egfGrid)
{
	ColorRGBA nut, egf;
	nut.r = nut.g = nut.b = nut.a = 1.0f;
	egf.r = egf.g = egf.b = egf.a = 1.0f;

	for (int i = 0; i < cells.size(); i++) {
		if ((cells[i].coordinates.x > this->minimumLimit.x && cells[i].coordinates.x < this->maximumLimit.x) && (cells[i].coordinates.y > this->minimumLimit.y && cells[i].coordinates.y < this->maximumLimit.y) && (cells[i].coordinates.z > this->minimumLimit.z && cells[i].coordinates.z < this->maximumLimit.z)) {

			nut.g = nutGrid[(int)round(cells[i].coordinates.x/accuracy)][(int)round(cells[i].coordinates.y/accuracy)][(int)round(cells[i].coordinates.z/accuracy)];
			egf.b = egfGrid[(int)round(cells[i].coordinates.x/accuracy)][(int)round(cells[i].coordinates.y/accuracy)][(int)round(cells[i].coordinates.z/accuracy)];

			switch (cells[i].type) {
				case NEC:
					if(cellDT.NEC.visibility) //Necrotic Cell (0): RGB DEPENDS ON CALCIFICATION LEVEL
						this->drawCell_(cells[i], viewMode, cellDT.NEC.color.primary, cellDT.NEC.color.secondary, nut, egf);

					break;
				case QUI:
					if(cellDT.QUI.visibility)
						this->drawCell_(cells[i], viewMode, cellDT.QUI.color.primary, cellDT.QUI.color.secondary, nut, egf);

					break;
				case PRO:
					if(cellDT.PRO.visibility)
						this->drawCell_(cells[i], viewMode, cellDT.PRO.color.primary, cellDT.PRO.color.secondary, nut, egf);

					break;
				case APO:
					if(cellDT.APO.visibility)
						this->drawCell_(cells[i], viewMode, cellDT.APO.color.primary, cellDT.APO.color.secondary, nut, egf);

					break;
				case G1:
					if(cellDT.G1.visibility)
						this->drawCell_(cells[i], viewMode, cellDT.G1.color.primary, cellDT.G1.color.secondary, nut, egf);

					break;
				case NOR:
					if(cellDT.NOR.visibility)
						this->drawCell_(cells[i], viewMode, cellDT.NOR.color.primary, cellDT.NOR.color.secondary, nut, egf);

					break;
			}
		}
	}
}

void ogl::Render::renderLines()
{
	glLineWidth(2.5);
	glColor3f(1.0, 0.0, 0.0);
	//Right
	glBegin(GL_LINES);
	glVertex3f(this->maximumLimit.x, this->min_.y, this->middle_.z);
	glVertex3f(this->maximumLimit.x, this->max_.y, this->middle_.z);
	glEnd();
	//Left
	glBegin(GL_LINES);
	glVertex3f(this->minimumLimit.x, this->min_.y, this->middle_.z);
	glVertex3f(this->minimumLimit.x, this->max_.y, this->middle_.z);
	glEnd();
	//Top
	glBegin(GL_LINES);
	glVertex3f(this->min_.x, this->maximumLimit.y, this->middle_.z);
	glVertex3f(this->max_.x, this->maximumLimit.y, this->middle_.z);
	glEnd();
	//Bottom
	glBegin(GL_LINES);
	glVertex3f(this->min_.x, this->minimumLimit.y, this->middle_.z);
	glVertex3f(this->max_.x, this->minimumLimit.y, this->middle_.z);
	glEnd();
	//Back
	glBegin(GL_LINES);
	glVertex3f(this->middle_.x - CELL_GAP, this->middle_.y, this->maximumLimit.z);
	glVertex3f(this->middle_.x + CELL_GAP, this->middle_.y, this->maximumLimit.z);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(this->middle_.x, this->middle_.y - CELL_GAP, this->maximumLimit.z);
	glVertex3f(this->middle_.x, this->middle_.y + CELL_GAP, this->maximumLimit.z);
	glEnd();
	//Front
	glBegin(GL_LINES);
	glVertex3f(this->middle_.x - CELL_GAP, this->middle_.y, this->minimumLimit.z);
	glVertex3f(this->middle_.x + CELL_GAP, this->middle_.y, this->minimumLimit.z);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(this->middle_.x, this->middle_.y - CELL_GAP, this->minimumLimit.z);
	glVertex3f(this->middle_.x, this->middle_.y + CELL_GAP, this->minimumLimit.z);
	glEnd();
}

Vector3 ogl::Render::getMiddle()
{
	return middle_;
}

Vector3 ogl::Render::getMin()
{
	return min_;
}

Vector3 ogl::Render::getMax()
{
	return max_;
}
