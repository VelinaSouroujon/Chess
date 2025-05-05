#include "Bishop.h"
#include "Move.h"

bool Bishop::isValidMove(const Move& move) const
{
	ChessCoordinate from = move.getFrom();
	ChessCoordinate to = move.getTo();

	return to.isSameDiagonal(from);
}
