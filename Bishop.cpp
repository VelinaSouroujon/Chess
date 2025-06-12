#include "Bishop.h"
#include "Move.h"

Bishop::Bishop(PieceColor color) : Piece(color)
{

}

char Bishop::getPieceNotation() const
{
	return Constants::BISHOP_NOTATION;
}

bool Bishop::isValidMove(const Move& move) const
{
	ChessCoordinate from = move.getFrom();
	ChessCoordinate to = move.getTo();

	return to.isSameDiagonal(from);
}

wchar_t Bishop::accept(const PieceRenderer& renderer) const
{
	return renderer.getRepresentation(*this);
}

Piece* Bishop::clone() const
{
	return new Bishop(*this);
}
