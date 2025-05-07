#include "King.h"
#include "Move.h"

char King::getPieceNotation() const
{
	return Constants::KING_NOTATION;
}

bool King::isValidMove(const Move& move) const
{
	ChessCoordinate from = move.getFrom();
	ChessCoordinate to = move.getTo();

	return from.isNeighborWith(to);
}
