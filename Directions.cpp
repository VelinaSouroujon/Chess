#include "Directions.h"

void Directions::fillRowDirections(Array<PieceDirection, Constants::MAX_DIRECTIONS_COUNT>& directions)
{
	PieceDirection left(-1, 0);
	PieceDirection right(1, 0);

	directions.add(left);
	directions.add(right);
}

void Directions::fillColDirections(Array<PieceDirection, Constants::MAX_DIRECTIONS_COUNT>& directions)
{
	PieceDirection up(0, 1);
	PieceDirection down(0, -1);

	directions.add(up);
	directions.add(down);
}

void Directions::fillDiagonalDirections(Array<PieceDirection, Constants::MAX_DIRECTIONS_COUNT>& directions)
{
	PieceDirection leftUp(-1, 1);
	directions.add(leftUp);

	PieceDirection rightUp(1, 1);
	directions.add(rightUp);

	PieceDirection leftDown(-1, -1);
	directions.add(leftDown);

	PieceDirection rightDown(1, -1);
	directions.add(rightDown);
}
