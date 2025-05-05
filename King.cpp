#include "King.h"
#include "Move.h"

bool King::isValidMove(const Move& move) const
{
	ChessCoordinate from = move.getFrom();
	ChessCoordinate to = move.getTo();

	return from.isNeighborWith(to);
}
