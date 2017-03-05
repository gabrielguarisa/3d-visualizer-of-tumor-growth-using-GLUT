#include "Render.h"
#include <cmath>
#include <iostream>

bool 	visibilityNEC = true,  /***  Necrotic Cell  ***/
		visibilityQUI = true,  /***  Quiescent Cell  ***/
		visibilityPRO = true,  /***  Proliferative Cell  ***/
		visibilityHIP = true,  /***  Hipoxic Cell  ***/
		visibilityAPO = true,  /***  Apoptotic Cell  ***/
		visibilityG1 = true,   /***  Cell G1 State  ***/
		visibilityNOR = true;  /***  Normal Cell  ***/

ViewMode viewMode = STD;

int frameNum = 0;
float accuracy = 10.0f;

std::vector<std::vector<std::vector<std::vector<float> > > > nutGrids;
std::vector<std::vector<std::vector<std::vector<float> > > > egfGrids;


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

			float _valueNut = nutGrids[frameNum][(int)round(cells[i].coordinates.x/accuracy)][(int)round(cells[i].coordinates.y/accuracy)][(int)round(cells[i].coordinates.z/accuracy)];
			float _valueEgf = egfGrids[frameNum][(int)round(cells[i].coordinates.x/accuracy)][(int)round(cells[i].coordinates.y/accuracy)][(int)round(cells[i].coordinates.z/accuracy)];

			glPushMatrix();
			glTranslatef(cells[i].coordinates.x, cells[i].coordinates.y, cells[i].coordinates.z);
			switch (cells[i].type) {
			case NEC: //Necrotic Cell (0): RGB DEPENDS ON CALCIFICATION LEVEL
				if(visibilityNEC)
				{
					if(viewMode == STD)
						glColor4f((cells[i].calcification)*1.0f, 0.0f, (1 - cells[i].calcification)*1.0f, 1.0f);
					else
					{
						if(viewMode == NUT)
							glColor4f(1.0f, _valueNut, 1.0f, 1.0f);
						else if(viewMode == EGF)
							glColor4f(1.0f, 1.0f, _valueEgf, 1.0f);
					}
					glutSolidSphere(cells[i].radius, NUM_SEGMENTS, NUM_SEGMENTS);
				}
				break;
			case QUI: //Quiescent Cell (1): RGB #CCCCFF & RGB #4D4DFF
				if(visibilityQUI)
				{
					if(viewMode == STD)
						glColor4f(0.302f, 0.302f, 1.0f, 1.0f);
					else
					{
						if(viewMode == NUT)
							glColor4f(1.0f, _valueNut, 1.0f, 1.0f);
						else if(viewMode == EGF)
							glColor4f(1.0f, 1.0f, _valueEgf, 1.0f);
					}
					glutSolidSphere(cells[i].nucleusRadius, NUM_SEGMENTS, NUM_SEGMENTS);
					glDepthMask(GL_FALSE);
					if(viewMode == STD)
						glColor4f(0.8f, 0.8f, 1.0f, 0.2f);
					else
					{
						if(viewMode == NUT)
							glColor4f(0.9f, _valueNut, 0.9f, 0.2f);
						else if(viewMode == EGF)
							glColor4f(0.9f, 0.9f, _valueEgf, 0.2f);
					}
					glutSolidSphere(cells[i].radius, NUM_SEGMENTS, NUM_SEGMENTS);
					glDepthMask(GL_TRUE);
				}
				break;
			case PRO: //Proliferative Cell (2): RGB #00CC00 & RGB #4D4DFF
				if(visibilityPRO)
				{
					if(viewMode == STD)
						glColor4f(0.302f, 0.302f, 1.0f, 1.0f);
					else
					{
						if(viewMode == NUT)
							glColor4f(1.0f, _valueNut, 1.0f, 1.0f);
						else if(viewMode == EGF)
							glColor4f(1.0f, 1.0f, _valueEgf, 1.0f);
					}

					glutSolidSphere(cells[i].nucleusRadius, NUM_SEGMENTS, NUM_SEGMENTS);
					glDepthMask(GL_FALSE);
					if(viewMode == STD)
						glColor4f(0.0f, 0.8f, 0.0f, 0.2f);
					else
					{
						if(viewMode == NUT)
							glColor4f(0.9f, _valueNut, 0.9f, 0.2f);
						else if(viewMode == EGF)
							glColor4f(0.9f, 0.9f, _valueEgf, 0.2f);
					}
					glutSolidSphere(cells[i].radius, NUM_SEGMENTS, NUM_SEGMENTS);
					glDepthMask(GL_TRUE);
				}
				break;
			case APO: //Apoptotic Cell (4): RGB #E60000 & RGB #4D4DFF
				if(visibilityAPO)
				{
					if(viewMode == STD)
						glColor4f(0.302f, 0.302f, 1.0f, 1.0f);
					else
					{
						if(viewMode == NUT)
							glColor4f(1.0f, _valueNut, 1.0f, 1.0f);
						else if(viewMode == EGF)
							glColor4f(1.0f, 1.0f, _valueEgf, 1.0f);
					}
					glutSolidSphere(cells[i].nucleusRadius, NUM_SEGMENTS, NUM_SEGMENTS);
					glDepthMask(GL_FALSE);
					if(viewMode == STD)
						glColor4f(0.902f, 0.0f, 0.0f, 0.2f);
					else
					{
						if(viewMode == NUT)
							glColor4f(0.9f, _valueNut, 0.9f, 0.2f);
						else if(viewMode == EGF)
							glColor4f(0.9f, 0.9f, _valueEgf, 0.2f);
					}
					glutSolidSphere(cells[i].radius, NUM_SEGMENTS, NUM_SEGMENTS);
					glDepthMask(GL_TRUE);
				}
				break;
			case G1: //G1 Cell (5): RGB #00CC00 & RGB #4D4DFF
				if(visibilityG1)
				{
					if(viewMode == STD)
						glColor4f(0.302f, 0.302f, 1.0f, 1.0f);
					else
					{
						if(viewMode == NUT)
							glColor4f(1.0f, _valueNut, 1.0f, 1.0f);
						else if(viewMode == EGF)
							glColor4f(1.0f, 1.0f, _valueEgf, 1.0f);
					}
					glutSolidSphere(cells[i].nucleusRadius, NUM_SEGMENTS, NUM_SEGMENTS);
					if(viewMode == STD)
						glColor4f(0.0f, 0.8f, 0.0f, 0.2f);
					else
					{
						if(viewMode == NUT)
							glColor4f(0.9f, _valueNut, 0.9f, 0.2f);
						else if(viewMode == EGF)
							glColor4f(0.9f, 0.9f, _valueEgf, 0.2f);
					}
					glDepthMask(GL_FALSE);
					glutSolidSphere(cells[i].radius, NUM_SEGMENTS, NUM_SEGMENTS);
					glDepthMask(GL_TRUE);
				}
				break;
			case NOR: //Normal Cell (6): RGB #E8E8F5 & RGB #DDDDF7
				if(visibilityNOR)
				{
					if(viewMode == STD)
						glColor4f(0.867f, 0.867f, 0.969f, 1.0f);
					else
					{
						if(viewMode == NUT)
							glColor4f(1.0f, _valueNut, 1.0f, 1.0f);
						else if(viewMode == EGF)
							glColor4f(1.0f, 1.0f, _valueEgf, 1.0f);
					}
					glutSolidSphere(cells[i].nucleusRadius, NUM_SEGMENTS, NUM_SEGMENTS);
					glDepthMask(GL_FALSE);
					if(viewMode == STD)
						glColor4f(0.91f, 0.91f, 0.961f, 0.2f);
					else
					{
						if(viewMode == NUT)
							glColor4f(0.9f, _valueNut, 0.9f, 0.2f);
						else if(viewMode == EGF)
							glColor4f(0.9f, 0.9f, _valueEgf, 0.2f);
					}

					glutSolidSphere(cells[i].radius, NUM_SEGMENTS, NUM_SEGMENTS);
					glDepthMask(GL_TRUE);
				}
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
