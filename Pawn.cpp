#include "Pawn.h"
#include "Move.h"

char Pawn::getPieceNotation() const
{
	return Constants::PAWN_NOTATION;
}

bool Pawn::isValidMove(const Move& move) const
{
	ChessCoordinate from = move.getFrom();
	ChessCoordinate to = move.getTo();

	if (move.isCaptureMove())
	{
		return to.getRow() - from.getRow() == (int)getColor()
			&& to.isSameDiagonal(from);
	}

	return to.getRow() - from.getRow() == (int)getColor()
		&& to.isSameCol(from);
}
