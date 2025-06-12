#include "King.h"
#include "Move.h"

King::King(PieceColor color) : Piece(color)
{

}

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

wchar_t King::accept(const PieceRenderer& renderer) const
{
	return renderer.getRepresentation(*this);
}

Piece* King::clone() const
{
	return new King(*this);
}
