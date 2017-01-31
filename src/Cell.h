#ifndef CELL
#define CELL

#include "Util.h"

class Cell
{
public:
	CellType type;

	Vector3 coordinates,
			speed;

	float	nucleusRadius,
			radius,
			actionRadius,
			lifetime,
			previousState,
			oConsumption,
			egfConsumption,
			calcification;

	Cell(CellType type, Vector3 coordinates, float nucleusRadius, float radius,
		float actionRadius, float lifetime, float previousState, float oConsumption,
		float egfConsumption, float calcification, Vector3 speed = Vector3())
		:
			type(type),
			coordinates(coordinates),
			nucleusRadius(nucleusRadius),
			radius(radius),
			actionRadius(actionRadius),
			lifetime(lifetime),
			previousState(previousState),
			oConsumption(oConsumption),
			egfConsumption(egfConsumption),
			calcification(calcification),
			speed(speed)
	{}

	Cell()
	{}
};

#endif /* end of include guard: CELL */
