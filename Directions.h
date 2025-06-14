#pragma once

#include "Array.hpp"
#include "PieceDirection.h"

namespace Directions
{
	void fillRowDirections(Array<PieceDirection, Constants::MAX_DIRECTIONS_COUNT>& directions);
	void fillColDirections(Array<PieceDirection, Constants::MAX_DIRECTIONS_COUNT>& directions);
	void fillDiagonalDirections(Array<PieceDirection, Constants::MAX_DIRECTIONS_COUNT>& directions);
}
