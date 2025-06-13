#include "Pawn.h"
#include "Move.h"
#include "CommonUtils.h"

void Pawn::setPosition(const ChessCoordinate& coordinate)
{
	const int EN_PASSANT_POSSIBLE_ROW_DIFF = 2;
	int absRowDiff = CommonUtils::abs(coordinate.getRow() - getPosition().getRow());

	MoveablePiece::setPosition(coordinate);

	if (absRowDiff == EN_PASSANT_POSSIBLE_ROW_DIFF)
	{
		mediator.notifyMove(*this);
	}
}

Pawn::Pawn(PieceColor color, PieceMediator& pawnMediator) 
	: MoveablePiece(color),
	mediator(pawnMediator)
{

}

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

wchar_t Pawn::accept(const PieceRenderer& renderer) const
{
	return renderer.getRepresentation(*this);
}

Piece* Pawn::clone() const
{
	return new Pawn(*this);
}
