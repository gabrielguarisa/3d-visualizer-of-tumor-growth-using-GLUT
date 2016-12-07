#include "Render.h"

ogl::Render::Render(Vector3 minimumLimit, Vector3 maximumLimit)
{
	this->minimumLimit = this->min_ = minimumLimit - CELL_GAP;
	this->maximumLimit = this->max_ = maximumLimit + CELL_GAP;
	this->middle_ = Vector3((min_.x + max_.x) / 2, (min_.y + max_.y) / 2, (min_.z + max_.z) / 2);
}

void ogl::Render::renderCells(std::vector<Cell> cells)
{
	for (int i = 0; i < cells.size(); i++) {
		if ((cells[i].coordinates.x > this->minimumLimit.x && cells[i].coordinates.x < this->maximumLimit.x) && (cells[i].coordinates.y > this->minimumLimit.y && cells[i].coordinates.y < this->maximumLimit.y) && (cells[i].coordinates.z > this->minimumLimit.z && cells[i].coordinates.z < this->maximumLimit.z)) {
			glPushMatrix();
			glTranslatef(cells[i].coordinates.x, cells[i].coordinates.y, cells[i].coordinates.z);
			switch (cells[i].type) {
			case NEC: //Necrotic Cell (0): RGB DEPENDS ON CALCIFICATION LEVEL
				glColor4f((cells[i].calcification)*1.0f, 0.0f, (1 - cells[i].calcification)*1.0f, 1.0f);
				glutSolidSphere(cells[i].radius, NUM_SEGMENTS, NUM_SEGMENTS);
				break;
			case QUI: //Quiescent Cell (1): RGB #CCCCFF & RGB #4D4DFF
				glColor4f(0.302f, 0.302f, 1.0f, 1.0f);
				glutSolidSphere(cells[i].nucleusRadius, NUM_SEGMENTS, NUM_SEGMENTS);
				glDepthMask(GL_FALSE);
				glColor4f(0.8f, 0.8f, 1.0f, 0.2f);
				glutSolidSphere(cells[i].radius, NUM_SEGMENTS, NUM_SEGMENTS);
				glDepthMask(GL_TRUE);
				break;
			case PRO: //Proliferative Cell (2): RGB #00CC00 & RGB #4D4DFF
				glColor4f(0.302f, 0.302f, 1.0f, 1.0f);
				glutSolidSphere(cells[i].nucleusRadius, NUM_SEGMENTS, NUM_SEGMENTS);
				glDepthMask(GL_FALSE);
				glColor4f(0.0f, 0.8f, 0.0f, 0.2f);
				glutSolidSphere(cells[i].radius, NUM_SEGMENTS, NUM_SEGMENTS);
				glDepthMask(GL_TRUE);
				break;
			case APO: //Apoptotic Cell (4): RGB #E60000 & RGB #4D4DFF
				glColor4f(0.302f, 0.302f, 1.0f, 1.0f);
				glutSolidSphere(cells[i].nucleusRadius, NUM_SEGMENTS, NUM_SEGMENTS);
				glDepthMask(GL_FALSE);
				glColor4f(0.902f, 0.0f, 0.0f, 0.2f);
				glutSolidSphere(cells[i].radius, NUM_SEGMENTS, NUM_SEGMENTS);
				glDepthMask(GL_TRUE);
				break;
			case G1: //G1 Cell (5): RGB #00CC00 & RGB #4D4DFF
				glColor4f(0.302f, 0.302f, 1.0f, 1.0f);
				glutSolidSphere(cells[i].nucleusRadius, NUM_SEGMENTS, NUM_SEGMENTS);
				glColor4f(0.0f, 0.8f, 0.0f, 0.2f);
				glDepthMask(GL_FALSE);
				glutSolidSphere(cells[i].radius, NUM_SEGMENTS, NUM_SEGMENTS);
				glDepthMask(GL_TRUE);
				break;
			case NOR: //Normal Cell (6): RGB #E8E8F5 & RGB #DDDDF7
				glColor4f(0.867f, 0.867f, 0.969f, 1.0f);
				glutSolidSphere(cells[i].nucleusRadius, NUM_SEGMENTS, NUM_SEGMENTS);
				glDepthMask(GL_FALSE);
				glColor4f(0.91f, 0.91f, 0.961f, 0.2f);
				glutSolidSphere(cells[i].radius, NUM_SEGMENTS, NUM_SEGMENTS);
				glDepthMask(GL_TRUE);
				break;
			default:
				glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
				glutSolidSphere(cells[i].nucleusRadius, NUM_SEGMENTS, NUM_SEGMENTS);
				break;

			}
			glPopMatrix();
		}
	}
}

void ogl::Render::renderLines()
{
	glLineWidth(2.5);
	glColor3f(1.0, 0.0, 0.0);
	//Right
	glBegin(GL_LINES);
	glVertex3f(this->maximumLimit.x, this->min_.y, 0);
	glVertex3f(this->maximumLimit.x, this->max_.y, 0);
	glEnd();
	//Left
	glBegin(GL_LINES);
	glVertex3f(this->minimumLimit.x, this->min_.y, 0);
	glVertex3f(this->minimumLimit.x, this->max_.y, 0);
	glEnd();
	//Top
	glBegin(GL_LINES);
	glVertex3f(this->min_.x, this->maximumLimit.y, 0);
	glVertex3f(this->max_.x, this->maximumLimit.y, 0);
	glEnd();
	//Bottom
	glBegin(GL_LINES);
	glVertex3f(this->min_.x, this->minimumLimit.y, 0);
	glVertex3f(this->max_.x, this->minimumLimit.y, 0);
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
