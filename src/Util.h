#pragma once

#include "Vector.h"
#include <GL/glut.h>
#include <map>

// Cell Types
typedef enum
{
	UND = -1, /***  Undefined Cell  ***/
	NEC = 0,  /***  Necrotic Cell  ***/
	QUI = 1,  /***  Quiescent Cell  ***/
	PRO = 2,  /***  Proliferative Cell  ***/
	HIP = 3,  /***  Hipoxic Cell  ***/
	APO = 4,  /***  Apoptotic Cell  ***/
	G1 = 5,   /***  Cell G1 State  ***/
	NOR = 6   /***  Normal Cell  ***/
} CellType;


typedef enum
{
	PNG,
	JPG
} ImageFormat;


typedef enum
{
	STD = 0,
	NUT = 1,
	EGF = 2
} ViewMode;
