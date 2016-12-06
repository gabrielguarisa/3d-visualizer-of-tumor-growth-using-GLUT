#pragma once

#include <GL/glut.h>

// Cell Types
typedef enum
{
	NEC = 0,  /***  Necrotic Cell  ***/
	QUI = 1,  /***  Quiescent Cell  ***/
	PRO = 2,  /***  Proliferative Cell  ***/
	HIP = 3,  /***  Hipoxic Cell  ***/
	APO = 4,  /***  Apoptotic Cell  ***/
	G1 = 5,   /***  Cell G1 State  ***/
	NOR = 6   /***  Normal Cell  ***/
} CellType;

class Vector3
{
public:
	GLfloat x, y, z;

	Vector3(GLfloat x = 0.0f, GLfloat y = 0.0f, GLfloat z = 0.0f)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};
