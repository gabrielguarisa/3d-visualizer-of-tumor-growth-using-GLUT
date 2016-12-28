#pragma once

#include "Vector3.h"

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


typedef enum
{
	PNG,
	JPG
} ImageFormat;