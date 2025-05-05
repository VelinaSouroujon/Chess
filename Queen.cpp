#include "Queen.h"
#include "Move.h"

bool Queen::isValidMove(const Move& move) const
{
	ChessCoordinate from = move.getFrom();
	ChessCoordinate to = move.getTo();

	return from.isSameRow(to)
		|| from.isSameCol(to)
		|| from.isSameDiagonal(to);
}
