#include "Render.h"
#include <cmath>
#include <iostream>

float accuracy = 10.0f;

void ogl::Render::drawCell_(Cell c, ViewMode viewMode, ColorRGBA primary, ColorRGBA secondary, double nutValue, double egfValue) {

	if(viewMode == NUT)
	{
		this->generateColor(&primary, nutValue);
		secondary = primary;
		secondary.a = 0.2;
	}
	else if(viewMode == EGF)
	{
		this->generateColor(&primary, egfValue, 0.0, 3.0);
		secondary = primary;
		secondary.a = 0.2;
	}

	glPushMatrix();

	glTranslatef(c.coordinates.x, c.coordinates.y, c.coordinates.z);

	if (c.type == NEC && viewMode == STD)
		glColor4f((c.calcification)*primary.r, primary.g, (1 - c.calcification)*primary.b, primary.a);
	else
		glColor4f(primary.r, primary.g, primary.b, primary.a);

	glutSolidSphere(c.nucleusRadius, NUM_SEGMENTS, NUM_SEGMENTS);


	glDepthMask(GL_FALSE);

	if (c.type == NEC && viewMode == STD)
		glColor4f((c.calcification)*secondary.r, secondary.g, (1 - c.calcification)*secondary.b, secondary.a);
	else
		glColor4f(secondary.r, secondary.g, secondary.b, secondary.a);

	glutSolidSphere(c.radius, NUM_SEGMENTS, NUM_SEGMENTS);

	glDepthMask(GL_TRUE);

	glPopMatrix();
}

void ogl::Render::renderCells(std::vector<Cell> cells, std::vector<std::vector<std::vector<float> > >  nutGrid, std::vector<std::vector<std::vector<float> > >  egfGrid, ConfigHandler* config)
{
	for (int i = 0; i < cells.size(); i++) {
		if ((cells[i].coordinates.x > config->display.lines.minimumLimit.x && cells[i].coordinates.x < config->display.lines.maximumLimit.x) && (cells[i].coordinates.y > config->display.lines.minimumLimit.y && cells[i].coordinates.y < config->display.lines.maximumLimit.y) && (cells[i].coordinates.z > config->display.lines.minimumLimit.z && cells[i].coordinates.z < config->display.lines.maximumLimit.z)) {
			//Calcula concetração de oxigênio na malha esparsa
			double sigma_oxg_1 = nutGrid[(int)(cells[i].coordinates.x/accuracy)][(int)(cells[i].coordinates.y/accuracy)][(int)(cells[i].coordinates.z/accuracy)];
			double sigma_oxg_2 = nutGrid[(int)(cells[i].coordinates.x/accuracy + 1)][(int)(cells[i].coordinates.y/accuracy)][(int)(cells[i].coordinates.z/accuracy)];
			double sigma_oxg_3 = nutGrid[(int)(cells[i].coordinates.x/accuracy)][(int)(cells[i].coordinates.y/accuracy + 1)][(int)(cells[i].coordinates.z/accuracy)];
			double sigma_oxg_4 = nutGrid[(int)(cells[i].coordinates.x/accuracy + 1)][(int)(cells[i].coordinates.y/accuracy + 1)][(int)(cells[i].coordinates.z/accuracy)];
			double sigma_oxg_5 = nutGrid[(int)(cells[i].coordinates.x/accuracy)][(int)(cells[i].coordinates.y/accuracy)][(int)(cells[i].coordinates.z/accuracy + 1)];
			double sigma_oxg_6 = nutGrid[(int)(cells[i].coordinates.x/accuracy + 1)][(int)(cells[i].coordinates.y/accuracy)][(int)(cells[i].coordinates.z/accuracy + 1)];
			double sigma_oxg_7 = nutGrid[(int)(cells[i].coordinates.x/accuracy)][(int)(cells[i].coordinates.y/accuracy + 1)][(int)(cells[i].coordinates.z/accuracy + 1)];
			double sigma_oxg_8 = nutGrid[(int)(cells[i].coordinates.x/accuracy + 1)][(int)(cells[i].coordinates.y/accuracy + 1)][(int)(cells[i].coordinates.z/accuracy + 1)];

			//Calcula EGF na malha esparsa
			double sigma_egf_1 = egfGrid[(int)(cells[i].coordinates.x/accuracy)][(int)(cells[i].coordinates.y/accuracy)][(int)(cells[i].coordinates.z/accuracy)];
			double sigma_egf_2 = egfGrid[(int)(cells[i].coordinates.x/accuracy + 1)][(int)(cells[i].coordinates.y/accuracy)][(int)(cells[i].coordinates.z/accuracy)];
			double sigma_egf_3 = egfGrid[(int)(cells[i].coordinates.x/accuracy)][(int)(cells[i].coordinates.y/accuracy + 1)][(int)(cells[i].coordinates.z/accuracy)];
			double sigma_egf_4 = egfGrid[(int)(cells[i].coordinates.x/accuracy + 1)][(int)(cells[i].coordinates.y/accuracy + 1)][(int)(cells[i].coordinates.z/accuracy)];
			double sigma_egf_5 = egfGrid[(int)(cells[i].coordinates.x/accuracy)][(int)(cells[i].coordinates.y/accuracy)][(int)(cells[i].coordinates.z/accuracy + 1)];
			double sigma_egf_6 = egfGrid[(int)(cells[i].coordinates.x/accuracy + 1)][(int)(cells[i].coordinates.y/accuracy)][(int)(cells[i].coordinates.z/accuracy + 1)];
			double sigma_egf_7 = egfGrid[(int)(cells[i].coordinates.x/accuracy)][(int)(cells[i].coordinates.y/accuracy + 1)][(int)(cells[i].coordinates.z/accuracy + 1)];
			double sigma_egf_8 = egfGrid[(int)(cells[i].coordinates.x/accuracy + 1)][(int)(cells[i].coordinates.y/accuracy + 1)][(int)(cells[i].coordinates.z/accuracy + 1)];

			//Calcula concetração de oxigênio na célula
			double x_cell = cells[i].coordinates.x - ((int)cells[i].coordinates.x);
			double y_cell = cells[i].coordinates.y - ((int)cells[i].coordinates.y);
			double z_cell = cells[i].coordinates.z - ((int)cells[i].coordinates.z);

			double nutValue = (1-x_cell/accuracy)*(1-y_cell/accuracy)*(1-z_cell/accuracy)*sigma_oxg_1 + (x_cell/accuracy)*(1-y_cell/accuracy)*(1-z_cell/accuracy)*sigma_oxg_2 + (1-x_cell/accuracy)*(y_cell/accuracy)*(1-z_cell/accuracy)*sigma_oxg_3 + (x_cell/accuracy)*(y_cell/accuracy)*(1-z_cell/accuracy)*sigma_oxg_4 + (1-x_cell/accuracy)*(1-y_cell/accuracy)*(z_cell/accuracy)*sigma_oxg_5 + (x_cell/accuracy)*(1-y_cell/accuracy)*(z_cell/accuracy)*sigma_oxg_6 + (1-x_cell/accuracy)*(y_cell/accuracy)*(z_cell/accuracy)*sigma_oxg_7 + (x_cell/accuracy)*(y_cell/accuracy)*(z_cell/accuracy)*sigma_oxg_8;
			double egfValue = (1-x_cell/accuracy)*(1-y_cell/accuracy)*(1-z_cell/accuracy)*sigma_egf_1 + (x_cell/accuracy)*(1-y_cell/accuracy)*(1-z_cell/accuracy)*sigma_egf_2 + (1-x_cell/accuracy)*(y_cell/accuracy)*(1-z_cell/accuracy)*sigma_egf_3 + (x_cell/accuracy)*(y_cell/accuracy)*(1-z_cell/accuracy)*sigma_egf_4 + (1-x_cell/accuracy)*(1-y_cell/accuracy)*(z_cell/accuracy)*sigma_egf_5 + (x_cell/accuracy)*(1-y_cell/accuracy)*(z_cell/accuracy)*sigma_egf_6 + (1-x_cell/accuracy)*(y_cell/accuracy)*(z_cell/accuracy)*sigma_egf_7 + (x_cell/accuracy)*(y_cell/accuracy)*(z_cell/accuracy)*sigma_egf_8;

			switch (cells[i].type) {
				case NEC:
					if(config->display.cells.NEC.visibility) //Necrotic Cell (0): RGB DEPENDS ON CALCIFICATION LEVEL
						this->drawCell_(cells[i], config->display.viewMode, config->display.cells.NEC.color.primary, config->display.cells.NEC.color.secondary, nutValue, egfValue);

					break;
				case QUI:
					if(config->display.cells.QUI.visibility)
						this->drawCell_(cells[i], config->display.viewMode, config->display.cells.QUI.color.primary, config->display.cells.QUI.color.secondary, nutValue, egfValue);

					break;
				case PRO:
					if(config->display.cells.PRO.visibility)
						this->drawCell_(cells[i], config->display.viewMode, config->display.cells.PRO.color.primary, config->display.cells.PRO.color.secondary, nutValue, egfValue);

					break;
				case APO:
					if(config->display.cells.APO.visibility)
						this->drawCell_(cells[i], config->display.viewMode, config->display.cells.APO.color.primary, config->display.cells.APO.color.secondary, nutValue, egfValue);

					break;
				case G1:
					if(config->display.cells.G1.visibility)
						this->drawCell_(cells[i], config->display.viewMode, config->display.cells.G1.color.primary, config->display.cells.G1.color.secondary, nutValue, egfValue);

					break;
				case NOR:
					if(config->display.cells.NOR.visibility)
						this->drawCell_(cells[i], config->display.viewMode, config->display.cells.NOR.color.primary, config->display.cells.NOR.color.secondary, nutValue, egfValue);

					break;
			}
		}
	}
}

void ogl::Render::generateColor(ColorRGBA *c, double value, double min, double max)
{
	double range = max - min;
	double temp;

	if ( value >= min  && value < (min + range/4.0) ){
		temp = (value - min)/( (range/4.0)/ 85);
		temp /= 85;

		c->r = 1;
		c->g = temp;
		c->b = 0;
	}
	if ( value >= (min + range/4.0)  && value < (min + range/2.0) ){
		temp = (value - (min + range/4.0))/( (range/4.0)/ 85);
		temp /= 85;

		c->r = (1 - temp);
		c->g = 1;
		c->b = 0;
	}
	if ( value >= (min + range/2.0)  && value < (min + 3*range/4.0) ){
		temp = (value - (min + range / 2.0)) / ((range/4.0) / 85);
		temp /= 85;

		c->r = 0;
		c->g = 1;
		c->b = temp;
	}
	if ( value >= (min + 3*range/4.0)  && value <= max ){
		temp = (value - (min + 3*range/4.0))/( (range/4.0)/ 85);
		temp /= 85;

		c->r = 0;
		c->g = (1 - temp);
		c->b = 1;
	}
	c->a = 1;
	//std::cout << c->r << "  " << c->g << "  " << c->b << std::endl;
}

void ogl::Render::renderLines(ConfigHandler* config)
{
	glPushMatrix();
	glDisable(GL_LIGHTING);

	glLineWidth(2.5);
	glColor3f(1.0, 0.0, 0.0);
	//Right
	glBegin(GL_LINES);
	glVertex3f(config->display.lines.maximumLimit.x, config->display.lines.minimumLimit.y, (config->display.lines.minimumLimit.z + config->display.lines.maximumLimit.z) / 2);
	glVertex3f(config->display.lines.maximumLimit.x, config->display.lines.maximumLimit.y, (config->display.lines.minimumLimit.z + config->display.lines.maximumLimit.z) / 2);
	glEnd();
	//Left
	glBegin(GL_LINES);
	glVertex3f(config->display.lines.minimumLimit.x, config->display.lines.minimumLimit.y, (config->display.lines.minimumLimit.z + config->display.lines.maximumLimit.z) / 2);
	glVertex3f(config->display.lines.minimumLimit.x, config->display.lines.maximumLimit.y, (config->display.lines.minimumLimit.z + config->display.lines.maximumLimit.z) / 2);
	glEnd();
	//Top
	glBegin(GL_LINES);
	glVertex3f(config->display.lines.minimumLimit.x, config->display.lines.maximumLimit.y, (config->display.lines.minimumLimit.z + config->display.lines.maximumLimit.z) / 2);
	glVertex3f(config->display.lines.maximumLimit.x, config->display.lines.maximumLimit.y, (config->display.lines.minimumLimit.z + config->display.lines.maximumLimit.z) / 2);
	glEnd();
	//Bottom
	glBegin(GL_LINES);
	glVertex3f(config->display.lines.minimumLimit.x, config->display.lines.minimumLimit.y, (config->display.lines.minimumLimit.z + config->display.lines.maximumLimit.z) / 2);
	glVertex3f(config->display.lines.maximumLimit.x, config->display.lines.minimumLimit.y, (config->display.lines.minimumLimit.z + config->display.lines.maximumLimit.z) / 2);
	glEnd();
	//Back
	glBegin(GL_LINES);
	glVertex3f(((config->display.lines.minimumLimit.x + config->display.lines.maximumLimit.x) / 2) - config->display.lines.cellGap, (config->display.lines.minimumLimit.y + config->display.lines.maximumLimit.y) / 2, config->display.lines.maximumLimit.z);
	glVertex3f(((config->display.lines.minimumLimit.x + config->display.lines.maximumLimit.x) / 2) + config->display.lines.cellGap, (config->display.lines.minimumLimit.y + config->display.lines.maximumLimit.y) / 2, config->display.lines.maximumLimit.z);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f((config->display.lines.minimumLimit.x + config->display.lines.maximumLimit.x) / 2, ((config->display.lines.minimumLimit.y + config->display.lines.maximumLimit.y) / 2) - config->display.lines.cellGap, config->display.lines.maximumLimit.z);
	glVertex3f((config->display.lines.minimumLimit.x + config->display.lines.maximumLimit.x) / 2, (config->display.lines.minimumLimit.y + config->display.lines.maximumLimit.y) / 2 + config->display.lines.cellGap, config->display.lines.maximumLimit.z);
	glEnd();
	//Front
	glBegin(GL_LINES);
	glVertex3f(((config->display.lines.minimumLimit.x + config->display.lines.maximumLimit.x) / 2) - config->display.lines.cellGap, (config->display.lines.minimumLimit.y + config->display.lines.maximumLimit.y) / 2, config->display.lines.minimumLimit.z);
	glVertex3f(((config->display.lines.minimumLimit.x + config->display.lines.maximumLimit.x) / 2) + config->display.lines.cellGap, (config->display.lines.minimumLimit.y + config->display.lines.maximumLimit.y) / 2, config->display.lines.minimumLimit.z);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f((config->display.lines.minimumLimit.x + config->display.lines.maximumLimit.x) / 2, ((config->display.lines.minimumLimit.y + config->display.lines.maximumLimit.y) / 2) - config->display.lines.cellGap, config->display.lines.minimumLimit.z);
	glVertex3f((config->display.lines.minimumLimit.x + config->display.lines.maximumLimit.x) / 2, ((config->display.lines.minimumLimit.y + config->display.lines.maximumLimit.y) / 2) + config->display.lines.cellGap, config->display.lines.minimumLimit.z);
	glEnd();

	glEnable(GL_LIGHTING);
	glPopMatrix();
}


void ogl::Render::axisDraw()
{
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glLineWidth(3.0);

	glTranslatef(-100, -50, 0);
	glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(50.0, 0.0, 0.0);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 50.0, 0.0);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 50.0);
	glEnd();

	glEnable(GL_LIGHTING);
	glLineWidth(1.0);
	glPopMatrix();
}
