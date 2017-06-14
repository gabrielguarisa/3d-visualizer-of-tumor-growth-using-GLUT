#ifndef CELL
#define CELL

#include "Util.hpp"

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

	double 	sigmaO,
			sigmaEGF;

	Cell(CellType type = UND, Vector3 coordinates = Vector3(), float nucleusRadius = 0.0f,
		float radius = 0.0f, float actionRadius = 0.0f, float lifetime = 0.0f,
		float previousState = 0.0f, float oConsumption = 0.0f, float egfConsumption = 0.0f,
		float calcification = 0.0f, Vector3 speed = Vector3(), double sigmaO = 0.0f, double sigmaEGF = 0.0f)
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
			speed(speed),
			sigmaO(sigmaO),
			sigmaEGF(sigmaEGF)
	{}
};

#endif /* end of include guard: CELL */
